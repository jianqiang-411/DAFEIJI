//
//  BossBulletOne.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-9.
//
//

#ifndef _______BossBulletOne__
#define _______BossBulletOne__

#include <iostream>
#include "DevilBullet.h"
class BossBulletOne:public DevilBullet
{
public:
    CREATE_FUNC(BossBulletOne);
    bool init();
};

#endif /* defined(_______BossBulletOne__) */
