#ifndef __SIGNALCHANGEDETECTOR_H_
#define __SIGNALCHANGEDETECTOR_H_

class SignalChangeDetector
{
    int previousValue_;
    int currentValue_;
    bool status_; // 値が変化する度にtrue/falseがトグルする
    bool updateFlag_;

public:
    SignalChangeDetector()
    {
        previousValue_ = 1;
        status_ = false; // 初期値はOFF
    }

    SignalChangeDetector(int firstValue, bool status = false)
    {
        previousValue_ = firstValue;
        status_ = status;
    }

    void Update();
    void Input(int x);
    bool IsChanged();
    bool IsChangedRise(); // OFF → ON
    bool IsChangedFall(); // ON → OFF
};

#endif