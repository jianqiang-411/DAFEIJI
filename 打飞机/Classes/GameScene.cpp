//
//  GameScene.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-6-27.
//
//

#include "GameScene.h"
#include "Defines.h"
using namespace cocos2d;
GameScene::GameScene()
{
    _gameLayer = NULL;
}

GameScene::~GameScene()
{
    
}

bool GameScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        
        int iGameOverTemp = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameOverTemp");
        if (iGameOverTemp != 1) {
            CCUD->setIntegerForKey("devilnum", DEVILNUM);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreNew", 0);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumNew", 0);
        }
        
        _gameLayer = GameLayer::create();
        this->addChild(_gameLayer, 0);
        
        bRet = true;
    } while(0);
    
    return bRet;
}
















