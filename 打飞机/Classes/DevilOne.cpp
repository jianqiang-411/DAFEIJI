//
//  DevilOne.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#include "DevilOne.h"
using namespace cocos2d;
DevilOne::DevilOne()
{
    _fDevilHp = NULL;
    _fDevilPower = NULL;
    _fDevilScore = NULL;
    _fDevilSpeed = NULL;
}

bool DevilOne::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("devil_01.png"));
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFDevilHp(120);
            this->setFDevilPower(60);
            this->setFDevilScore(300);
            this->setFDevilSpeed(150);
        }
        else if (iSeclectValue == 1) {
            this->setFDevilHp(30);
            this->setFDevilPower(20);
            this->setFDevilScore(100);
            this->setFDevilSpeed(50);
        }
        else {
            this->setFDevilHp(60);
            this->setFDevilPower(40);
            this->setFDevilScore(200);
            this->setFDevilSpeed(100);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}












































