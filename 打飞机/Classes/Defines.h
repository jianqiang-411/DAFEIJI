//
//  Defines.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-2.
//
//

#ifndef _______Defines__
#define _______Defines__

#include <iostream>
#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define DIRECTOR CCDirector::sharedDirector()
#define CCUD CCUserDefault::sharedUserDefault()

#define USERFLUSH CCUserDefault::sharedUserDefault()->flush();\
CCUserDefault::sharedUserDefault()->purgeSharedUserDefault()

#define DEVILNUM 15 //控制怪物一出现的数量
#define DEVILTWONUM 2 //分批出现的怪物数量

#define HEROBULLETRADIUS 18 //英雄子弹半径
#define HERORADIUS 26      //英雄半径
#define DEVILBULLETRADIUS 6    //怪物子弹半径
#define DEVILRADIUS 20     //怪物1半径
#define DEVILTWORADIUS 15     //怪物2半径
#define BOSSRADIUS 80  //BOSS半径

#define HEROHP 300 //英雄总血量
#define BOSSHPA 400  //BOSS总血量
#define BOSSHPB 700
#define BOSSHPC 100

#endif /* defined(_______Defines__) */
