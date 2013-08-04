//
//  GameOverLayer.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-1.
//
//

#include "GameOverLayer.h"
#include "LoadingView.h"
#include "GameScene.h"
#include "Defines.h"
using namespace cocos2d;
GameOverLayer::GameOverLayer()
{
    _spriteRestart = NULL;
}

GameOverLayer::~GameOverLayer()
{
    
}

bool GameOverLayer::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        
        this->initView();
        
        pRet = true;
    } while(0);
    
    return pRet;
}

#pragma mark - 初始化画面
void GameOverLayer::initView()
{
    this->initBackground();
    this->initbutn();
    this->initScore();
    
    int iGameOverTemp = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameOverTemp");
    if (iGameOverTemp == 1) {
        this->GameWin();
    }else if (iGameOverTemp == 2){
        this->GameLose();
    }
}

#pragma mark - 背景
void GameOverLayer::initBackground()
{
    CCSprite *backgroundSprite = CCSprite::create("xingkong_02.png");
    backgroundSprite->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2));
    this->addChild(backgroundSprite, -5);
}

#pragma mark - 胜利操作
void GameOverLayer::GameWin()
{
//    CCLabelTTF *restartLabel = CCLabelTTF::create("You Win!", "Arial", 30);
//    restartLabel->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2));
//    this->addChild(restartLabel, 5);
    
    CCSprite *spriteWin = CCSprite::create("win_small_02.png");
    spriteWin->setPosition(ccp(SCREEN.width / 2 + 5, SCREEN.height / 2 + 50));
    this->addChild(spriteWin);
    
    CCActionInterval *scaleTo= CCScaleTo::create(2, 2);
    spriteWin->runAction(scaleTo);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameOverLayer::spriteWin));
    spriteWin->runAction(CCSequence::create(scaleTo, actionMoveDone, NULL));    
}

void GameOverLayer::spriteWin()
{
    CCSprite *spriteKing = CCSprite::create("first_01.png");
    spriteKing->setPosition(ccp(165, 500));
    this->addChild(spriteKing);
    
    CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(165, 355));
    spriteKing->runAction(moveTo);
}


#pragma mark - 失败操作
void GameOverLayer::GameLose()
{
    CCSprite *spriteLose = CCSprite::create("lose_03.png");
    spriteLose->setPosition(ccp(SCREEN.width / 2 - 5, SCREEN.height / 2 + 273));//273
    this->addChild(spriteLose, 1);
    
    CCMoveTo *moveTo = CCMoveTo::create(0.2, ccp(SCREEN.width / 2 - 5, SCREEN.height / 2 + 140));
    CCActionInterval *jumpTo = CCJumpTo::create(1, ccp(SCREEN.width / 2 - 5, SCREEN.height / 2 + 90), 50, 1);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameOverLayer::spriteLose));
    spriteLose->runAction(CCSequence::create(moveTo, jumpTo, actionMoveDone, NULL));
    
    _spriteRestart = CCSprite::create("restart_01.png");//restart_01, 140
    _spriteRestart->setPosition(ccp(SCREEN.width / 2 - 5, SCREEN.height / 2 + 50));
    this->addChild(_spriteRestart);
}

void GameOverLayer::spriteLose()
{
    this->removeChild(_spriteRestart, true);
    
    CCMenuItemImage *itemImgRestart = CCMenuItemImage::create("restart_small_01.png", "restart_small_01.png", this, menu_selector(GameOverLayer::restartGame));
    itemImgRestart->setPosition(ccp(SCREEN.width / 2 - 5, SCREEN.height / 2 + 50));
    
    CCMenu *restartGame = CCMenu::create(itemImgRestart, NULL);
    restartGame->setPosition(CCPointZero);
    this->addChild(restartGame, 6);
}

void GameOverLayer::restartGame()
{
    CCDirector::sharedDirector()->replaceScene(GameScene::create());
}

#pragma mark - 返回按钮和下一关按钮
void GameOverLayer::initbutn()
{
    CCMenuItemImage *itemBack = CCMenuItemImage::create("back_01.png", "back_01.png", this, menu_selector(GameOverLayer::selectBack));
    itemBack->setPosition(ccp(230, 40));
    
    CCMenuItemImage *itemNext = CCMenuItemImage::create("next_01.png", "next_01.png", this, menu_selector(GameOverLayer::selectNext));
    itemNext->setPosition(ccp(275, 40));
    
    CCMenu *menuButn = CCMenu::create(itemBack, itemNext, NULL);
    menuButn->setPosition(CCPointZero);
    this->addChild(menuButn, 6);
}

void GameOverLayer::selectBack()
{
    LoadingView *loadingView = LoadingView::create();
    DIRECTOR->replaceScene(loadingView);
}

void GameOverLayer::selectNext()
{
    DIRECTOR->replaceScene(GameScene::create());
}

#pragma mark - 得分
void GameOverLayer::initScore()
{
    CCLabelTTF *labScoreTitle = CCLabelTTF::create("得分", "Arial", 40);
    labScoreTitle->setColor(ccc3(255, 234, 3));
    labScoreTitle->setPosition(ccp(85, 200));
    this->addChild(labScoreTitle);
    
    int iScoreNew = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreNew");
    CCLog("-------%i", iScoreNew);
    CCString *chScore = CCString::createWithFormat("%d",iScoreNew);
    CCLog("-------%s", chScore);
    CCLabelTTF *labScore = CCLabelTTF::create(chScore->getCString(), "Arial", 40);
    labScore->setPosition(ccp(400, 198));
    this->addChild(labScore);
    
    CCActionInterval *ske1 = CCSkewTo::create(0.1, 50, 0);
    CCMoveTo *moveTo = CCMoveTo::create(0.3, ccp(200, 198));
    CCActionInterval *ske2 = CCSkewTo::create(0.2, -30, 0);
    CCActionInterval *ske3 = CCSkewTo::create(0.1, 0, 0);
    CCFiniteTimeAction *seq = CCSequence::create(ske1, moveTo, ske2, ske3, NULL);
    labScore->runAction(seq);
    
    int iGameOverTemp = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameOverTemp");
    if (iGameOverTemp != 1) {
        this->updataScore();
    }
}

#pragma mark - 刷新分数记录
void GameOverLayer::updataScore()
{
    int _scoreNew = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreNew");
    int scoreFirst = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreFirst");
    int scoreSecond = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreSecond");
    int scoreThird = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreThird");
    int scoreForth = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreForth");
    int scoreFifth = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreFifth");
    
    int _numNew = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumNew");
    int devilNumFirst = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumFirst");
    int devilNumSecond = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumSecond");
    int devilNumThird = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumThird");
    int devilNumForth = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumForth");
    int devilNumFifth = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumFifth");
    
    int temp = 0;
    
    //1
    if (_scoreNew != 0 || scoreFirst != 0) {
        if (_scoreNew > scoreFirst) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreFirst", _scoreNew);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumFirst", _numNew);
            USERFLUSH;
            
            temp = scoreFirst;
            scoreFirst = _scoreNew;
            _scoreNew = temp;
            temp = devilNumFirst;
            devilNumFirst = _numNew;
            _numNew = temp;
        }
        else if (_scoreNew == scoreFirst) {
            if (_numNew > devilNumFirst) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumFirst", _numNew);
                USERFLUSH;
                temp = _numNew;
                _numNew = devilNumFirst;
                devilNumFirst = temp;
            }
        }
    }
    
    //2
    if (_scoreNew != 0 || scoreSecond != 0) {
        if (_scoreNew > scoreSecond) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreSecond", _scoreNew);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumSecond", _numNew);
            
            USERFLUSH;
            temp = scoreSecond;
            scoreSecond = _scoreNew;
            _scoreNew = temp;
            temp = devilNumSecond;
            devilNumSecond = _numNew;
            _numNew = temp;
        }
        else if (_scoreNew == scoreSecond) {
            if (_numNew > devilNumSecond) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumSecond", _numNew);
                USERFLUSH;
                temp = _numNew;
                _numNew = devilNumSecond;
                devilNumSecond = temp;
            }
        }
    }
    
    //3
    if (_scoreNew != 0 || scoreThird != 0) {
        if (_scoreNew > scoreThird) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreThird", _scoreNew);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumThird", _numNew);
            USERFLUSH;
            temp = scoreThird;
            scoreThird = _scoreNew;
            _scoreNew = temp;
            temp = devilNumThird;
            devilNumThird = _numNew;
            _numNew = temp;
        }
        else if (_scoreNew == scoreThird) {
            if (_numNew > devilNumThird) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumThird", _numNew);
                USERFLUSH;
                temp = _numNew;
                _numNew = devilNumThird;
                devilNumThird = temp;
            }
        }
    }
    
    //4
    if (_scoreNew != 0 || scoreForth != 0) {
        if (_scoreNew > scoreForth) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreForth", _scoreNew);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumForth", _numNew);
            USERFLUSH;
            temp = scoreForth;
            scoreForth = _scoreNew;
            _scoreNew = temp;
            temp = devilNumForth;
            devilNumForth = _numNew;
            _numNew = temp;
        }
        else if (_scoreNew == scoreForth) {
            if (_numNew > devilNumForth) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumForth", _numNew);
                USERFLUSH;
                temp = _numNew;
                _numNew = devilNumForth;
                devilNumForth = temp;
            }
        }
    }
    
    //5
    if (_scoreNew != 0 || scoreFifth != 0) {
        if (_scoreNew > scoreFifth) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreFifth", _scoreNew);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumFifth", _numNew);
            USERFLUSH;
            temp = scoreFifth;
            scoreFifth = _scoreNew;
            _scoreNew = temp;
            temp = devilNumFifth;
            devilNumFifth = _numNew;
            _numNew = temp;
        }
        else if (_scoreNew == scoreFifth) {
            if (_numNew > devilNumFifth) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumFifth", _numNew);
                USERFLUSH;
                temp = _numNew;
                _numNew = devilNumFifth;
                devilNumFifth = temp;
            }
        }
    }
    
    //清空新纪录
    CCUD->setIntegerForKey("scoreNew", 0);
    CCUD->setIntegerForKey("devilNumNew", 0);
    USERFLUSH;
}



















