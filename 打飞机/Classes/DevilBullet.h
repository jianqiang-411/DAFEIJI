//
//  DevilBullet.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#ifndef _______DevilBullet__
#define _______DevilBullet__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class DevilBullet:public CCSprite
{
public:
    CREATE_FUNC(DevilBullet);
    
    DevilBullet();
    
    CC_SYNTHESIZE(float, _fDevilBulletPower, FDevilBulletPower);//怪物子弹攻击
    CC_SYNTHESIZE(float, _fDevilBulletSpeed, FDevilBulletSpeed);//怪物子弹攻击
    
    virtual bool init();
};

#endif /* defined(_______DevilBullet__) */
