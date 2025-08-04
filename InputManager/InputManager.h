// スイッチ入力補助クラス
// 20241015Ver.
//
// 使い方
// インスタンス作成時に読みたい入力ピンを指定
// フレームの冒頭でCheckInput()メンバを呼ぶ
// CheckInput()呼び出し後、GetKey()メンバで今のスイッチの状態が返る（GetKey()内でdigitalReadを呼び出し、その値を返却している）
// CheckInput()呼び出し後、GetKeyDown()メンバ・GetKeyUp()メンバで連射対策されたスイッチの状態が返る
//   GetKeyDown()の場合：押した瞬間のみtrueを返却、GetKeyUp()の場合：離した瞬間のみtrueを返却
// フレームの最後でUpdate()メンバを呼ぶ

#ifndef __INPUT_MANAGER_H_
#define __INPUT_MANAGER_H_

class InputManager
{
  unsigned char pin_;

  int previousValue_;
  int currentValue_;

  bool updateFlag_;

public:
  InputManager(unsigned char pin) { pin_ = pin; previousValue_ = 1; updateFlag_ = false; };

  void SetFirstValueH();
  void SetFirstValueL();

  int CheckInput();
  bool GetKey() const;
  bool GetKeyDown() const;
  bool GetKeyUp() const;
  void Update();
};

#endif