// Unityでシリアル通信で送られてくるデータをデコードする雛形
// 2025_8月Ver.


using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoSomething : MonoBehaviour
{
    // 制御対象のオブジェクト用に宣言しておいて、Start関数内で名前で検索
    GameObject targetObject;
    
    // 制御対象にアタッチされたスクリプト
    Main targetScript; // この記述ではアタッチするGameObjectにMainスクリプトがアタッチされている必要がある

    // シリアル通信のクラス、クラス名は正しく書くこと
    public SerialHandler serialHandler;

  void Start()
    {
        // 制御対象のオブジェクトを取得、このオブジェクトにMain.csが関連付けられている
        targetObject = GameObject.Find("GameMaster"); // この記述ではUnityのヒエラルキーにGameMasterオブジェクトがいる必要がある。

        // 制御対象にアタッチされたスクリプトを取得。
        // 大文字、小文字を区別するので、player.csを作ったのなら「p」layer。
        targetScript = targetObject.GetComponent<Main>(); // Mainスクリプトがアタッチされている必要がある

        // 信号受信時に呼ばれる関数としてOnDataReceived関数を登録
        serialHandler.OnDataReceived += OnDataReceived;
    }

    void Update()
    {
        // UnityからArduinoに送る場合はココに記述
        string command = "hogehoge";
        serialHandler.Write(command);
    }

    //受信した信号(message)に対する処理
    void OnDataReceived(string message)
    {
        if (message == null)
            return;

        // ここでデコード処理等を記述
    }
}
