//
//  IRNodeObjectAnimation.cpp
//  IRiMaS
//
//  Created by Keitaro on 13/03/2020.
//

#include "IRNodeObjectAnimation.hpp"

IRNodeObjectAnimation::IRNodeObjectAnimation(IRNodeComponent* obj) :
obj(obj)
{
    
}

IRNodeObjectAnimation::~IRNodeObjectAnimation()
{
    
}

// ============================================================


bool IRNodeObjectAnimation::tryTrigerAnimation(float currentTime)
{
    if(currentTime >= this->beginTime &&
       currentTime < this->endTime)
    {
        return true;
    }else{
        return false;
    }
}

void IRNodeObjectAnimation::setCurrentTimeCode(float currentTime)
{
    this->currentTimeCode = currentTime;
}

// ============================================================

void IRNodeObjectAnimation::showObject()
{
    this->obj->showThisObject(true);
}
void IRNodeObjectAnimation::hideObject()
{
    this->obj->showThisObject(false);
}
void IRNodeObjectAnimation::moveStart()
{
    
}
void IRNodeObjectAnimation::moveStop()
{
    
}

// ============================================================
void IRNodeObjectAnimation::setBeginTimeCode(float newBeginTimeCode)
{
    this->beginTime = newBeginTimeCode;
    StatusUpdated();
}

void IRNodeObjectAnimation::setEndTimeCode(float newEndTimeCode)
{
    this->endTime = newEndTimeCode;
    StatusUpdated();
}
// ============================================================

void IRNodeObjectAnimation::actionStart()
{
    showObject();
}
void IRNodeObjectAnimation::actionEnd()
{
    hideObject();
}
// ============================================================
// ============================================================
