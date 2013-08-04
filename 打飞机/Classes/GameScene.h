//
//  GameScene.h
//  打飞机
//
//  Created by 阚 庭树 on 13-6-27.
//
//

#ifndef _______GameScene__
#define _______GameScene__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
using namespace cocos2d;
class GameScene:public CCScene
{
public:
    CREATE_FUNC(GameScene);
    
    CC_SYNTHESIZE(GameLayer *, _gameLayer, GameLayer);//游戏场景
    
    GameScene();
    ~GameScene();
    
    virtual bool init();
};

#endif /* defined(_______GameScene__) */
