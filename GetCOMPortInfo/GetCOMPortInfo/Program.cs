// System.IO.PortsとSystem.Managementを使うためにNuGetでパッケージを取得する
// NuGetパッケージマネージャーでSystem.IO.PortsとSystem.Managementを検索・追加

using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Management;
using System.Runtime.Versioning;
using System.Text.RegularExpressions;

class Program
{
    [SupportedOSPlatform("windows")] // .NETはクロスプラットフォーム対応のため、これがないとWindows専用の関数を呼んでいる場合に警告が出る

    static void Main()
    {
        // COMポート一覧の取得
        // COMxxの数字順に並べ替えて取得
        var ports = SerialPort.GetPortNames().OrderBy(p => int.Parse(p.Substring(3))).ToList(); // 3はCOMの3文字を取り除くため

        // デバイス情報のうち「(COM」がついているものを取得し、LISTに追加
        var searcher = new ManagementObjectSearcher(
            "SELECT * FROM Win32_PnPEntity WHERE Name LIKE '%(COM%'"
            );

        var devices = new List<string>();
        foreach (ManagementObject mo in searcher.Get())
        {
            if (mo["Name"] is string s)
            {
                devices.Add(s);
            }
        }

        // 辞書に保存
        var map = new Dictionary<string, string>();
        foreach (var dev in devices)
        {
            var match = Regex.Match(dev, @"\(COM\d+\)");
            if (match.Success)
            {
                string portName = match.Value.Trim('(', ')'); // "例：COM3"
                map[portName] = dev; // 例：COM3 -> "USB-SERIAL CH340 (COM3)"
            }
        }

        foreach (var port in ports)
        {
            if (map.TryGetValue(port, out string? devName))
            {
                Console.WriteLine($"{port}\n{devName}");
            }
            else
            {
                Console.WriteLine($"{port}\nデバイス情報なし");
            }
        }
    }
}
