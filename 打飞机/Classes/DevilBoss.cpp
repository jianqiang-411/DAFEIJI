//
//  DevilBoss.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-9.
//
//

#include "DevilBoss.h"
#include "Defines.h"
using namespace cocos2d;
bool DevilBoss::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("boss_02_01.png"));
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFDevilHp(BOSSHPC);
            this->setFDevilPower(300);
            this->setFDevilScore(5000);
            this->setFDevilSpeed(200);
        }
        else if (iSeclectValue == 1) {
            this->setFDevilHp(BOSSHPA);
            this->setFDevilPower(100);
            this->setFDevilScore(1000);
            this->setFDevilSpeed(50);
        }
        else {
            this->setFDevilHp(BOSSHPB);
            this->setFDevilPower(200);
            this->setFDevilScore(2500);
            this->setFDevilSpeed(100);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}