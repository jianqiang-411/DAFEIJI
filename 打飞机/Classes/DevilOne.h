//
//  DevilOne.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#ifndef _______DevilOne__
#define _______DevilOne__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class DevilOne:public CCSprite
{
public:
    CREATE_FUNC(DevilOne);
    
    DevilOne();
    
    CC_SYNTHESIZE(float, _fDevilSpeed, FDevilSpeed);//怪物移动速度
    CC_SYNTHESIZE(float, _fDevilHp, FDevilHp);//怪物血量
    CC_SYNTHESIZE(float, _fDevilPower, FDevilPower);//怪物本身的攻击
    CC_SYNTHESIZE(float, _fDevilScore, FDevilScore);//怪物分数
    
    virtual bool init();
};

#endif /* defined(_______DevilOne__) */
