//
//  HeroBullet.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#ifndef _______HeroBullet__
#define _______HeroBullet__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class HeroBullet:public CCSprite
{
public:
    CREATE_FUNC(HeroBullet);
    
    HeroBullet();
    
    CC_SYNTHESIZE(float, _fHeroBulletPower, FHeroBulletPower);//英雄子弹攻击
    CC_SYNTHESIZE(float, _fHeroBulletSpeed, FHeroBulletSpeed);//英雄子弹攻击
    
    virtual bool init();
};

#endif /* defined(_______HeroBullet__) */
