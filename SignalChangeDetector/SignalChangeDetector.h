#ifndef __SIGNALCHANGEDETECTOR_H_
#define __SIGNALCHANGEDETECTOR_H_

class SignalChangeDetector
{
    int previousValue_;
    int currentValue_;
    bool status_; // 値が変化する度にtrue/falseがトグルする
    bool updateFlag_;

    int threshold_;

public:
    SignalChangeDetector(int firstValue = 1)
    {
        previousValue_ = firstValue;
        status_ = false; // 初期値はOFF
        threshold_ = -1;
    }

    SignalChangeDetector(int threshold, int firstValue)
    {
        previousValue_ = firstValue;
        status_ = false;
        threshold_ = threshold;
    }

    void Update();
    void Input(int x);
    bool IsChanged();
    bool IsChangedRise(); // OFF → ON
    bool IsChangedFall(); // ON → OFF
};

#endif