// Unityでシリアル通信を制御するクラス
// 例えば空のGameObjectを作り、そこにアタッチする
// 2025_10月Ver.

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System.IO.Ports; // これを通すために、Api Compatibility Levelの設定を変更
using System.Threading;
using System;

public class SerialHandler : MonoBehaviour
{
    public delegate void SerialDataReceivedEventHandler(string message);
    public event SerialDataReceivedEventHandler OnDataReceived;

    // COM10以上は\\\\.\\を付加しないと開けない。
    // portNameに直接代入すると失敗するので、ここでいったん別の変数に代入し、AwakeでportNameに代入
	// myPortNameが空文字列であればOpenを呼ばない＝デバイスがなくてもアプリケーションを実行することができる
    string myPortName = "\\\\.\\COM4";
    public int bitRate = 115200;

    public string portName;
    
    SerialPort serialPort_;
    Thread thread_;
    bool isRunning_ = false;

    string message_;
    bool isNewMessageReceived_ = false;

    // Use this for initialization
    void Start()
    {

    }

    void Awake()
    {
        if (myPortName != "")
        {
            portName = myPortName;
            Open();
        }
    }

    void Update()
    {
        if (isNewMessageReceived_)
        {
            OnDataReceived(message_);
        }
        isNewMessageReceived_ = false;
    }

    void OnDestroy()
    {
        if (isRunning_)
        {
            Close();
        }
    }

    private void Open()
    {
        serialPort_ = new SerialPort(portName, bitRate, Parity.None, 8, StopBits.One);

        serialPort_.NewLine = "\n"; // 行の最後に改行をつける設定

        serialPort_.RtsEnable = true;
        serialPort_.DtrEnable = true;

        serialPort_.Open();

        isRunning_ = true;

        thread_ = new Thread(Read);
        thread_.Start();
    }

    private void Close()
    {
        isNewMessageReceived_ = false;
        isRunning_ = false;

        if (serialPort_ != null && serialPort_.IsOpen)
        {
            serialPort_.Close();
        }

        if (thread_ != null && thread_.IsAlive)
        {
            if (!thread_.Join(500)) // 500msは適当な時間
            {
                // 少し待って応答がなければ強制終了
                Debug.LogWarning("from SerialHandler.cs Close(): Abort");
                thread_.Abort();
            }
        }

        if (serialPort_ != null)
        {
            serialPort_.Dispose();
        }
    }

    private void Read()
    {
        while (isRunning_ && serialPort_ != null && serialPort_.IsOpen)
        {
            try
            {
                message_ = serialPort_.ReadLine(); // 改行付きデータが送られる前提
                isNewMessageReceived_ = true;

                /* 69行目の変更の代わりにこちらでも可　この場合その時にバッファにあるものすべて読むのでずれに注意
                string raw = serialPort_.ReadExisting();

                if (!string.IsNullOrEmpty(raw))
                {
                    message_ = raw;
                    isNewMessageReceived_ = true;
                }
                */
            }
            catch (TimeoutException)
            {
                // このタイムアウトは通常の状態なのでスルーする
            }
            catch (System.Exception e)
            {
                if (!isRunning_)
                    break;

                Debug.LogWarning("from SerialHandler.cs Read(): " + e.Message);
            }
        }
    }

    public void Write(string message)
    {
        try
        {
            serialPort_.Write(message);
        }
        catch (System.Exception e)
        {
            Debug.LogWarning("from SerialHandler.cs Write(): " + e.Message);
        }
    }
}
