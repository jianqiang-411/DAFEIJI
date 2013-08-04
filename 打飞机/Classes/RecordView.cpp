//
//  RecordView.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-3.
//
//

#include "RecordView.h"
#include "LoadingView.h"
#include "Defines.h"
using namespace cocos2d;
RecordView::RecordView()
{
    _itemImgClear = NULL;
    _labFirstNum = NULL;
    _labFirstScore = NULL;
    _labSecondNum = NULL;
    _labSecondScore = NULL;
    _labThirdNum = NULL;
    _labThirdScore = NULL;
    _labForthNum = NULL;
    _labForthScore = NULL;
    _labFifthNum = NULL;
    _labFifthScore = NULL;
    _spriteBackground = NULL;
    _labAlock = NULL;
    _menuYESorNO = NULL;
    
}

RecordView::~RecordView()
{
    
}

bool RecordView::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        i = 0;
        
        this->recordMenuCreate();
        this->recordBackground();
        this->initClear();
        
        pRet = true;
    } while(0);
    
    return pRet;
}

#pragma mark -  清楚记录按钮
void RecordView::initClear()
{
    _itemImgClear = CCMenuItemImage::create("clear_01.png", "clear_01.png", this, menu_selector(RecordView::clearSpriteAction));
    _itemImgClear->setPosition(ccp(230, 540));
    
    _menu = CCMenu::create(_itemImgClear, NULL);
    _menu->setPosition(CCPointZero);
    this->addChild(_menu);
}

#pragma mark -  清楚记录按钮动画
void RecordView::clearSpriteAction()
{
    CCMoveTo *moveTo = CCMoveTo::create(0.2, ccp(230, 480));
    CCActionInterval *rotateTo1 = CCRotateTo::create(0.4, 16);
    CCActionInterval *rotateTo2 = CCRotateTo::create(0.6, -8);
    CCActionInterval *rotateTo3 = CCRotateTo::create(0.2, 4);
    CCActionInterval *rotateTo4 = CCRotateTo::create(0.1, 0);
    CCCallFuncN *actionDone = CCCallFuncN::create(this, callfuncN_selector(RecordView::clearButnCreate));
    CCFiniteTimeAction *seq = CCSequence::create(moveTo, rotateTo1, rotateTo2, rotateTo3, rotateTo4, actionDone, NULL);
    _itemImgClear->runAction(seq);
}

#pragma mark -  清楚记录按钮创建
void RecordView::clearButnCreate()
{
    this->removeChild(_itemImgClear, true);
    this->removeChild(_menu, true);
    
    _itemImgClear = CCMenuItemImage::create("clear_01.png", "clear_01.png", this, menu_selector(RecordView::yesORno));//selectClear
    _itemImgClear->setPosition(ccp(230, 480));
    
    _menu = CCMenu::create(_itemImgClear, NULL);
    _menu->setPosition(CCPointZero);
    this->addChild(_menu, 5);
}

void RecordView::yesORno()
{
    if (i == 0) {
        _spriteBackground = CCSprite::create("tishikuang_01.png");
        _spriteBackground->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2));
        //    spriteBackground->setOpacity(150);
        this->addChild(_spriteBackground, 6);
        
        _labAlock = CCLabelTTF::create("清楚所有记录", "Arial", 26);
        _labAlock->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2 + 35));
        this->addChild(_labAlock, 7);
        
        CCLabelTTF *labYES = CCLabelTTF::create("YES", "Arial", 26);
        CCMenuItemLabel *itemYES = CCMenuItemLabel::create(labYES, this, menu_selector(RecordView::selectClear));
        itemYES->setPosition(ccp(SCREEN.width / 2 - 45, SCREEN.height / 2 - 40));
        
        CCLabelTTF *labNO = CCLabelTTF::create("NO", "Arial", 26);
        CCMenuItemLabel *itemNO = CCMenuItemLabel::create(labNO, this, menu_selector(RecordView::selectNO));
        itemNO->setPosition(ccp(SCREEN.width / 2 + 45, SCREEN.height / 2 - 40));
        
        _menuYESorNO= CCMenu::create(itemYES, itemNO, NULL);
        _menuYESorNO->setPosition(CCPointZero);
        this->addChild(_menuYESorNO, 7);
    }
    i++;
    
}

#pragma mark -  背景
void RecordView::recordBackground()
{
    CCSprite *backgroundSprite = CCSprite::create("xingkong_02.png");
    backgroundSprite->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2));
    this->addChild(backgroundSprite, -1);
}

#pragma mark -  返回按键
void RecordView::recordMenuCreate()
{
    
    //皇冠
    CCSprite *spriteKing = CCSprite::create("king_01.png");
    spriteKing->setPosition(ccp(SCREEN.width / 2 - 50, 430));
    this->addChild(spriteKing, 0);
    
    //标题
    CCLabelTTF *labTitle = CCLabelTTF::create("英雄榜", "Arial", 30);
    labTitle->setPosition(ccp(SCREEN.width / 2 + 35, 420));
    this->addChild(labTitle, 0);
    
    //副标题栏
    CCLabelTTF *labHero = CCLabelTTF::create("排名", "Arial", 23);
    labHero->setPosition(ccp(SCREEN.width / 2 - 105, 360));
    this->addChild(labHero, 0);
    
    CCLabelTTF *labDevil = CCLabelTTF::create("歼敌", "Arial", 23);
    labDevil->setPosition(ccp(SCREEN.width / 2 - 20, 360));
    this->addChild(labDevil, 0);
    
    CCLabelTTF *labScore = CCLabelTTF::create("总分", "Arial", 23);
    labScore->setPosition(ccp(SCREEN.width / 2 + 80, 360));
    this->addChild(labScore, 0);
    
    //详细排名
    this->scoreDisplay();
    
    //返回
    CCLabelTTF *labBack = CCLabelTTF::create("返回", "Arial", 23);
    CCMenuItemLabel *itemBack = CCMenuItemLabel::create(labBack, this, menu_selector(RecordView::selectBack));
    itemBack->setPosition(ccp(240, 60));
    
    CCMenu *menuRecord = CCMenu::create(itemBack, NULL);
    menuRecord->setPosition(CCPointZero);
    this->addChild(menuRecord, 0);
}

#pragma mark - 排名展示
void RecordView::scoreDisplay()
{
    this->displayFirst();
    this->displaySecond();
    this->displayThird();
    this->displayForth();   
    this->displayFifth();
}

#pragma mark - 分数更新
void RecordView::scoreUpdata()
{
    
}

#pragma mark - 返回选择框
void RecordView::selectBack()
{
    LoadingView *_loadingView = LoadingView::create();
    DIRECTOR->replaceScene(_loadingView);
}

void RecordView::selectClear()
{
    CCUD->setIntegerForKey("scoreNew", 0);
    CCUD->setIntegerForKey("scoreFirst", 0);
    CCUD->setIntegerForKey("scoreSecond", 0);
    CCUD->setIntegerForKey("scoreThird", 0);
    CCUD->setIntegerForKey("scoreForth", 0);
    CCUD->setIntegerForKey("scoreFifth", 0);
    
    CCUD->setIntegerForKey("devilNumNew", 0);
    CCUD->setIntegerForKey("devilNumFirst", 0);
    CCUD->setIntegerForKey("devilNumSecond", 0);
    CCUD->setIntegerForKey("devilNumThird", 0);
    CCUD->setIntegerForKey("devilNumForth", 0);
    CCUD->setIntegerForKey("devilNumFifth", 0);
    
    this->removeChild(_labFirstScore, true);
    this->removeChild(_labSecondScore, true);
    this->removeChild(_labThirdScore, true);
    this->removeChild(_labForthScore, true);
    this->removeChild(_labFifthScore, true);
    this->removeChild(_labFirstNum, true);
    this->removeChild(_labSecondNum, true);
    this->removeChild(_labThirdNum, true);
    this->removeChild(_labForthNum, true);
    this->removeChild(_labFifthNum, true);
    
    this->selectNO();
    
    USERFLUSH;
}

void RecordView::selectNO()
{
    this->removeChild(_spriteBackground, true);
    this->removeChild(_labAlock, true);
    this->removeChild(_itemImgClear, true);
    this->removeChild(_menu, true);
    this->removeChild(_menuYESorNO, true);
    
    CCDirector::sharedDirector()->replaceScene(RecordView::create());
}

#pragma mark - 分数展示
#pragma mark - 排名1
void RecordView::displayFirst()
{
    int scoreFirst = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreFirst");
    int devilNumFirst = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumFirst");
    
    //1
    CCSprite *spriteFirst = CCSprite::create("first_01.png");
    spriteFirst->setPosition(ccp(SCREEN.width / 2 - 105, 320));
    this->addChild(spriteFirst, 0);
    
    CCSprite *spriteFirst1 = CCSprite::create("henggang_01.png");
    spriteFirst1->setPosition(ccp(SCREEN.width / 2 - 20, 320));
    this->addChild(spriteFirst1, 0);
    
    CCSprite *spriteFirst2 = CCSprite::create("henggang_01.png");
    spriteFirst2->setPosition(ccp(SCREEN.width / 2 + 80, 320));
    this->addChild(spriteFirst2, 0);
    
    if (scoreFirst != 0) {
        this->removeChild(spriteFirst1, true);
        this->removeChild(spriteFirst2, true);
        
        CCString *str1_1 = CCString::createWithFormat("%i", scoreFirst);
        CCString *str1_2 = CCString::createWithFormat("%i", devilNumFirst);
        
        _labFirstScore = CCLabelTTF::create(str1_1->getCString(), "Arial", 23);
        _labFirstNum = CCLabelTTF::create(str1_2->getCString(), "Arial", 23);
        _labFirstScore->setPosition(ccp(SCREEN.width / 2 + 80, 320));
        _labFirstNum->setPosition(ccp(SCREEN.width / 2 - 20, 320));
        this->addChild(_labFirstScore);
        this->addChild(_labFirstNum);
    }
}

#pragma mark - 排名2
void RecordView::displaySecond()
{
    int scoreSecond = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreSecond");
    int devilNumSecond = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumSecond");
    
    //2
    CCSprite *spriteSecond = CCSprite::create("second_01.png");
    spriteSecond->setPosition(ccp(SCREEN.width / 2 - 105, 280));
    this->addChild(spriteSecond, 0);
    
    CCSprite *spriteSecond1 = CCSprite::create("henggang_01.png");
    spriteSecond1->setPosition(ccp(SCREEN.width / 2 - 20, 280));
    this->addChild(spriteSecond1, 0);
    
    CCSprite *spriteSecond2 = CCSprite::create("henggang_01.png");
    spriteSecond2->setPosition(ccp(SCREEN.width / 2 + 80, 280));
    this->addChild(spriteSecond2, 0);
    
    if (scoreSecond != 0) {
        this->removeChild(spriteSecond1, true);
        this->removeChild(spriteSecond2, true);
        
        CCString *str1_1 = CCString::createWithFormat("%i", scoreSecond);
        CCString *str1_2 = CCString::createWithFormat("%i", devilNumSecond);
        
        _labSecondScore = CCLabelTTF::create(str1_1->getCString(), "Arial", 23);
        _labSecondNum = CCLabelTTF::create(str1_2->getCString(), "Arial", 23);
        _labSecondScore->setPosition(ccp(SCREEN.width / 2 + 80, 280));
        _labSecondNum->setPosition(ccp(SCREEN.width / 2 - 20, 280));
        this->addChild(_labSecondScore);
        this->addChild(_labSecondNum);
    }
}

#pragma mark - 排名3
void RecordView::displayThird()
{
    int scoreThird = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreThird");
    int devilNumThird = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumThird");
    
    //3
    CCSprite *spriteThird = CCSprite::create("third_01.png");
    spriteThird->setPosition(ccp(SCREEN.width / 2 - 105, 240));
    this->addChild(spriteThird, 0);
    
    CCSprite *spriteThird1 = CCSprite::create("henggang_01.png");
    spriteThird1->setPosition(ccp(SCREEN.width / 2 - 20, 240));
    this->addChild(spriteThird1, 0);
    
    CCSprite *spriteThird2 = CCSprite::create("henggang_01.png");
    spriteThird2->setPosition(ccp(SCREEN.width / 2 + 80, 240));
    this->addChild(spriteThird2, 0);
    
    if (scoreThird != 0) {
        this->removeChild(spriteThird1, true);
        this->removeChild(spriteThird2, true);
        
        CCString *str1_1 = CCString::createWithFormat("%i", scoreThird);
        CCString *str1_2 = CCString::createWithFormat("%i", devilNumThird);
        
        _labThirdScore = CCLabelTTF::create(str1_1->getCString(), "Arial", 23);
        _labThirdNum = CCLabelTTF::create(str1_2->getCString(), "Arial", 23);
        _labThirdScore->setPosition(ccp(SCREEN.width / 2 + 80, 240));
        _labThirdNum->setPosition(ccp(SCREEN.width / 2 - 20, 240));
        this->addChild(_labThirdScore);
        this->addChild(_labThirdNum);
    }
}

#pragma mark - 排名4
void RecordView::displayForth()
{
    int scoreForth = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreForth");
    int devilNumForth = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumForth");
    
    //4
    CCSprite *spriteForth = CCSprite::create("forth_01.png");
    spriteForth->setPosition(ccp(SCREEN.width / 2 - 105, 200));
    this->addChild(spriteForth, 0);
    
    CCSprite *spriteForth1 = CCSprite::create("henggang_01.png");
    spriteForth1->setPosition(ccp(SCREEN.width / 2 - 20, 200));
    this->addChild(spriteForth1, 0);
    
    CCSprite *spriteForth2 = CCSprite::create("henggang_01.png");
    spriteForth2->setPosition(ccp(SCREEN.width / 2 + 80, 200));
    this->addChild(spriteForth2, 0);
    
    if (scoreForth != 0) {
        this->removeChild(spriteForth1, true);
        this->removeChild(spriteForth2, true);
        
        CCString *str1_1 = CCString::createWithFormat("%i", scoreForth);
        CCString *str1_2 = CCString::createWithFormat("%i", devilNumForth);
        
        _labForthScore = CCLabelTTF::create(str1_1->getCString(), "Arial", 23);
        _labForthNum = CCLabelTTF::create(str1_2->getCString(), "Arial", 23);
//        lab1_2->setColor(ccc3(200, 200, 200));
        _labForthScore->setPosition(ccp(SCREEN.width / 2 + 80, 200));
        _labForthNum->setPosition(ccp(SCREEN.width / 2 - 20, 200));
        this->addChild(_labForthScore);
        this->addChild(_labForthNum);
    }
}

#pragma mark - 排名5
void RecordView::displayFifth()
{
    int scoreFifth = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreFifth");
    int devilNumFifth = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumFifth");
    
    //5
    CCSprite *spriteFifth = CCSprite::create("forth_01.png");
    spriteFifth->setPosition(ccp(SCREEN.width / 2 - 105, 160));
    this->addChild(spriteFifth, 0);
    
    CCSprite *spriteFifth1 = CCSprite::create("henggang_01.png");
    spriteFifth1->setPosition(ccp(SCREEN.width / 2 - 20, 160));
    this->addChild(spriteFifth1, 0);
    
    CCSprite *spriteFifth2 = CCSprite::create("henggang_01.png");
    spriteFifth2->setPosition(ccp(SCREEN.width / 2 + 80, 160));
    this->addChild(spriteFifth2, 0);
    
    if (scoreFifth != 0) {
        this->removeChild(spriteFifth1, true);
        this->removeChild(spriteFifth2, true);
        
        CCString *str1_1 = CCString::createWithFormat("%i", scoreFifth);
        CCString *str1_2 = CCString::createWithFormat("%i", devilNumFifth);
        
        _labFifthScore = CCLabelTTF::create(str1_1->getCString(), "Arial", 23);
        _labFifthNum = CCLabelTTF::create(str1_2->getCString(), "Arial", 23);
        _labFifthNum->setColor(ccc3(0, 0, 0));
        _labFifthScore->setPosition(ccp(SCREEN.width / 2 + 80, 160));
        _labFifthNum->setPosition(ccp(SCREEN.width / 2 - 20, 160));
        this->addChild(_labFifthScore);
        this->addChild(_labFifthNum);
    }
}























