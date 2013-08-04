//
//  LoadingView.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-3.
//
//

#include "LoadingView.h"
#include "GameScene.h"
#include "Defines.h"
#include "OptionView.h"
#include "RecordView.h"

using namespace cocos2d;
#pragma mark - 初始化
LoadingView::LoadingView()
{
//    _optionView = NULL;
//    _recordView = NULL;
//    _gameScene = NULL;
}

LoadingView::~LoadingView()
{
    
}

bool LoadingView::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        
        this->initBackground();
        this->initMenus();
        
        pRet = true;
    } while(0);
    
    return pRet;
}


#pragma mark - 背景画面
void LoadingView::initBackground()
{
    CCSprite *backgroundSprite = CCSprite::create("loading_background_01.png");
    backgroundSprite->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2));
    this->addChild(backgroundSprite);
}

#pragma mark - 选项栏
void LoadingView::initMenus()
{
    //开始游戏
    CCLabelTTF *labStart = CCLabelTTF::create("STRAT", "Arial", 21);
    labStart->setColor(ccc3(40, 40, 40));
    CCMenuItemLabel *itemStart = CCMenuItemLabel::create(labStart, this, menu_selector(LoadingView::startGame));
    itemStart->setPosition(ccp(SCREEN.width / 2, 220));
    
    CCSprite *sp = CCSprite::create("menu_02.png");
    sp->setPosition(itemStart->getPosition());
    sp->setOpacity(150);
    this->addChild(sp, 0);
    
    //游戏选项
    CCLabelTTF *laboPtion = CCLabelTTF::create("OPTION", "Arial", 21);
    laboPtion->setColor(ccc3(40, 40, 40));
    CCMenuItemLabel *itemOption = CCMenuItemLabel::create(laboPtion, this, menu_selector(LoadingView::optionGame));
    itemOption->setPosition(ccp(SCREEN.width / 2, 170));
    
    CCSprite *sp1 = CCSprite::create("menu_02.png");
    sp1->setPosition(itemOption->getPosition());
    sp1->setOpacity(150);
    this->addChild(sp1, 0);
    
    //排行榜
    CCLabelTTF *labrecord = CCLabelTTF::create("RECORD", "Arial", 21);
    labrecord->setColor(ccc3(40, 40, 40));
    CCMenuItemLabel *itemrecord = CCMenuItemLabel::create(labrecord, this, menu_selector(LoadingView::recordGame));
    itemrecord->setPosition(ccp(SCREEN.width / 2, 120));
    
    CCSprite *sp2 = CCSprite::create("menu_02.png");
    sp2->setPosition(itemrecord->getPosition());
    sp2->setOpacity(150);
    this->addChild(sp2, 0);
    
    //退出游戏
    CCLabelTTF *labExit = CCLabelTTF::create("EXIT", "Arial", 21);
    labExit->setColor(ccc3(40, 40, 40));
    CCMenuItemLabel *itemExit = CCMenuItemLabel::create(labExit, this, menu_selector(LoadingView::exitGame));
    itemExit->setPosition(ccp(SCREEN.width / 2, 70));
    
    CCSprite *sp3 = CCSprite::create("menu_02.png");
    sp3->setPosition(itemExit->getPosition());
    sp3->setOpacity(150);
    this->addChild(sp3, 0);
   
    //加入菜单事件
    CCMenu *_menu = CCMenu::create(itemStart, itemOption, itemrecord, itemExit, NULL);
    _menu->setPosition(CCPointZero);
    this->addChild(_menu, 1);
}

#pragma mark - 开始游戏
void LoadingView::startGame()
{
    GameScene *_gameScene = GameScene::create();
    DIRECTOR->replaceScene(_gameScene);
}

#pragma mark - 游戏设置页面
void LoadingView::optionGame()
{
    OptionView *_optionView = OptionView::create();
    DIRECTOR->replaceScene(_optionView);
}


#pragma mark - 游戏记录页面
void LoadingView::recordGame()
{
    RecordView *_recordView = RecordView::create();
    DIRECTOR->replaceScene(_recordView);
}


#pragma mark - 退出游戏
void LoadingView::exitGame()
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}















