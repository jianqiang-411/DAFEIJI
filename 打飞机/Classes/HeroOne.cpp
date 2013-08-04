//
//  HeroOne.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#include "HeroOne.h"
#include "Defines.h"
using namespace cocos2d;
HeroOne::HeroOne()
{
    _fHeroHp = NULL;
    _fHeroPower = NULL;
}

bool HeroOne::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("hero_03.png"));
        
        this->setFHeroHp(HEROHP);
        this->setFHeroPower(200);
//        this->setFHeroPower(10000);
        
        
        pRet = true;
    } while(0);
    
    return pRet;
}