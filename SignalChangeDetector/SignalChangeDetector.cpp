#include "SignalChangeDetector.h"

void SignalChangeDetector::Update()
{
    if (updateFlag_)
    {
        previousValue_ = currentValue_;
        updateFlag_ = false;
    }
}

void SignalChangeDetector::Input(int x)
{
    updateFlag_ = true;
    currentValue_ = x;
    if (currentValue_ != previousValue_)
        status_ = !status_;
}

bool SignalChangeDetector::IsChanged()
{
    if (currentValue_ != previousValue_)
        return true;
    else
        return false;
}

bool SignalChangeDetector::IsChangedRise()
{
    if (currentValue_ != previousValue_)
        if(status_) // 現在の状態がONのときはOFF→ON
            return true;

    return false;
}

bool SignalChangeDetector::IsChangedFall()
{
    if (currentValue_ != previousValue_)
        if(!status_) // 現在の状態がOFFのときはON→OFF
            return true;

    return false;
}
