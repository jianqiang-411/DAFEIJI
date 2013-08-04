//
//  BossBulletTwo.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-9.
//
//

#include "BossBulletTwo.h"
using namespace cocos2d;
bool BossBulletTwo::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("boss_zidan_02.png"));
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFDevilBulletPower(80);
            this->setFDevilBulletSpeed(400);
        }
        else if (iSeclectValue == 1) {
            this->setFDevilBulletPower(20);
            this->setFDevilBulletSpeed(200);
        }
        else {
            this->setFDevilBulletPower(40);
            this->setFDevilBulletSpeed(300);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}