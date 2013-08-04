//
//  BossBulletOne.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-9.
//
//

#include "BossBulletOne.h"
using namespace cocos2d;
bool BossBulletOne::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("boss_zidan_01.png"));//圆形
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFDevilBulletPower(60);
            this->setFDevilBulletSpeed(250);
        }
        else if (iSeclectValue == 1) {
            this->setFDevilBulletPower(1);
            this->setFDevilBulletSpeed(150);
        }
        else {
            this->setFDevilBulletPower(40);
            this->setFDevilBulletSpeed(200);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}