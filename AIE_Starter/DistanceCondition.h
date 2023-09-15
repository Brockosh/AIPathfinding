#pragma once
#include "Condition.h"
class DistanceCondition :
    public Condition
{
private:
    float distanceThreshhold;
    bool lessThan;

public:
    DistanceCondition(float d, bool checkIfLessThan) : distanceThreshhold(d), lessThan(checkIfLessThan) {}
    virtual bool IsTrue(Agent* agent);
};