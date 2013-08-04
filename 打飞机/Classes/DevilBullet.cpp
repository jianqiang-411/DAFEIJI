//
//  DevilBullet.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#include "DevilBullet.h"
using namespace cocos2d;
DevilBullet::DevilBullet()
{
    _fDevilBulletPower = NULL;
    _fDevilBulletSpeed = NULL;
}

bool DevilBullet::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("diren_zidan.png"));
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFDevilBulletPower(30);
            this->setFDevilBulletSpeed(200);
        }
        else if (iSeclectValue == 1) {
            this->setFDevilBulletPower(10);
            this->setFDevilBulletSpeed(100);
        }
        else {
            this->setFDevilBulletPower(20);
            this->setFDevilBulletSpeed(150);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}