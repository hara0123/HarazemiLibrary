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

#include "InputManager.h"
#include "Arduino.h"

void InputManager::SetFirstValueH()
{
  previousValue_ = 1;
}

void InputManager::SetFirstValueL()
{
  previousValue_ = 0;
}

void InputManager::Update()
{
  if(updateFlag_)
  {
    previousValue_ = currentValue_;
    updateFlag_ = false;
  }
}

int InputManager::CheckInput()
{
  updateFlag_ = true;
  currentValue_ = digitalRead(pin_);
  return currentValue_;
}

bool InputManager::GetKeyDown() const
{
  if(currentValue_ == 0 && previousValue_ == 1)
    return true;
  else
    return false;
}

bool InputManager::GetKeyUp() const
{
  if(currentValue_ == 1 && previousValue_ == 0)
    return true;
  else
    return false;
}

bool InputManager::GetKey() const
{
  if(currentValue_ == 0)
    return true;
  else
    return false;
}