//
//  GameOverLayer.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-1.
//
//

#ifndef _______GameOverLayer__
#define _______GameOverLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class GameOverLayer:public CCScene
{
public:
    CREATE_FUNC(GameOverLayer);
    
    GameOverLayer();
    ~GameOverLayer();
    
    CC_SYNTHESIZE(CCSprite *, _spriteRestart, SpriteRestart);
    
    bool init();
    
    void GameWin();
    void GameLose();
    void initView();
    void initBackground();
    void initbutn();
    void initScore();
    void selectBack();
    void selectNext();
    void spriteLose();
    void restartGame();
    void spriteWin();
    void newScore();
    void updataScore();
};

#endif /* defined(_______GameOverLayer__) */
