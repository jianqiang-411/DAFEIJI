//
//  HeroOne.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#ifndef _______HeroOne__
#define _______HeroOne__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class HeroOne:public CCSprite
{
public:
    CREATE_FUNC(HeroOne);
    
    HeroOne();
    
    CC_SYNTHESIZE(float, _fHeroHp, FHeroHp);//英雄血量
    CC_SYNTHESIZE(float, _fHeroPower, FHeroPower);//英雄本身攻击
    
    virtual bool init();
};

#endif /* defined(_______HeroOne__) */
