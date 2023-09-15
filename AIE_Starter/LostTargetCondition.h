#pragma once
#include "Condition.h"
class LostTargetCondition :
    public Condition
{
private:
    float distanceThreshold;
public:
    LostTargetCondition(float d) : distanceThreshold(d) {};
    virtual bool IsTrue(Agent* agent);
};