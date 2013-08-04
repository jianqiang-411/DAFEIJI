//
//  DevilTwo.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#include "DevilTwo.h"
using namespace cocos2d;
bool DevilTwo::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("devil_03_01.png"));
        
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFDevilHp(80);
            this->setFDevilPower(70);
            this->setFDevilScore(600);
            this->setFDevilSpeed(250);
        }
        else if (iSeclectValue == 1) {
            this->setFDevilHp(20);
            this->setFDevilPower(30);
            this->setFDevilScore(200);
            this->setFDevilSpeed(100);
        }
        else {
            this->setFDevilHp(40);
            this->setFDevilPower(50);
            this->setFDevilScore(400);
            this->setFDevilSpeed(175);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}