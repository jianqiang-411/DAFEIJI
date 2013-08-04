//
//  HeroBullet.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#include "HeroBullet.h"
using namespace cocos2d;
HeroBullet::HeroBullet()
{
    _fHeroBulletPower = NULL;
    _fHeroBulletSpeed = NULL;
}

bool HeroBullet::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("hero_zidan_03.png"));
        
//        this->setFHeroBulletPower(20);
//        this->setFHeroBulletSpeed(250);
        
        int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
        
        if (iSeclectValue == 3) {
            this->setFHeroBulletPower(60);
            this->setFHeroBulletSpeed(300);
        }
        else if (iSeclectValue == 1) {
            this->setFHeroBulletPower(20);
            this->setFHeroBulletSpeed(200);
        }
        else {
            this->setFHeroBulletPower(40);
            this->setFHeroBulletSpeed(250);
        }
        
        pRet = true;
    } while(0);
    
    return pRet;
}










