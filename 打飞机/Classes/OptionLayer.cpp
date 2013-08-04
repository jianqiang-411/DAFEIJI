//
//  OptionLayer.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-4.
//
//

#include "OptionLayer.h"
#include "LoadingView.h"
#include "Defines.h"
using namespace cocos2d;
OptionLayer::OptionLayer()
{
    _itemImgEasy = NULL;
    _itemImgEasy = NULL;
    _itemImgDifficulty = NULL;
    _itemImgBack = NULL; 
    _menuOption = NULL;
    _selectSprite = NULL;
    _selectMusic = NULL;
    _selectSound = NULL;
    
    _tishi = NULL;
}

bool OptionLayer::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->initSelect();
        
        this->optionViewCreate();
        
        pRet = true;
    } while(0);
    
    return pRet;
}

#pragma mark - 初始化选择框
void OptionLayer::initSelect()
{
    //默认普通难度
    _selectSprite = CCSprite::create("kuang_gou_01.png");
    this->addChild(_selectSprite, 1);
    
    
    _selectMusic = CCSprite::create("kuang_gou_01.png");
    this->addChild(_selectMusic,1);
    
    _selectSound = CCSprite::create("kuang_gou_01.png");
    this->addChild(_selectSound, 1);
}


#pragma mark - 创建选项菜单
void OptionLayer::optionViewCreate()
{
    this->optionBackground();//创建背景
    this->optionMenu();
}

#pragma mark - 背景画面
void OptionLayer::optionBackground()
{
    CCSprite *backgroundSprite = CCSprite::create("xingkong_02.png");
    backgroundSprite->setPosition(ccp(SCREEN.width / 2, SCREEN.height / 2));
    this->addChild(backgroundSprite, -5);
}

#pragma mark - 选项
void OptionLayer::optionMenu()
{
    //标题
    CCLabelTTF *labTitle = CCLabelTTF::create("选项设置", "Arial", 30);
    labTitle->setPosition(ccp(SCREEN.width / 2, 430));
    this->addChild(labTitle);
    
    //音乐
    CCLabelTTF *labMusic = CCLabelTTF::create("音乐", "Arial", 23);
    labMusic->setPosition(ccp(50, 350));
    this->addChild(labMusic);
    
    CCMenuItemImage *itemImgMusic = CCMenuItemImage::create("kuang_03.png", "kuang_03.png", this, menu_selector(OptionLayer::selectMusicDefault));
    itemImgMusic->setPosition(ccp(90, 350));
    
    //音效
    CCLabelTTF *labSound = CCLabelTTF::create("音效", "Arial", 23);
    labSound->setPosition(ccp(50, 315));
    this->addChild(labSound);
    
    CCMenuItemImage *itemImgSound = CCMenuItemImage::create("kuang_03.png", "kuang_03.png", this, menu_selector(OptionLayer::selectSoundDefault));
    itemImgSound->setPosition(ccp(90, 315));
    
    //难易度
    CCLabelTTF *labDifficulty = CCLabelTTF::create("难易度", "Arial", 23);
    labDifficulty->setPosition(ccp(60, 265));
    this->addChild(labDifficulty);
    
    //难易度参数设置, 默认普通难度
    //    CCUserDefault::sharedUserDefault()->setIntegerForKey("selectValue", 2);
    
    CCLabelTTF *labEasy = CCLabelTTF::create("简单", "Arial", 23);
    labEasy->setPosition(ccp(80, 230));
    this->addChild(labEasy);
    
    CCLabelTTF *labGeneral = CCLabelTTF::create("普通", "Arial", 23);
    labGeneral->setPosition(ccp(160, 230));
    this->addChild(labGeneral);
    
    CCLabelTTF *labDiff = CCLabelTTF::create("困难", "Arial", 23);
    labDiff->setPosition(ccp(240, 230));
    this->addChild(labDiff);
    
    //固定选框
    _itemImgEasy = CCMenuItemImage::create("kuang_03.png", "kuang_03.png", this, menu_selector(OptionLayer::selectEasy));
    _itemImgEasy->setPosition(ccp(45, 230));
    
    _itemImgGenerily = CCMenuItemImage::create("kuang_03.png", "kuang_03.png", this, menu_selector(OptionLayer::selectGenerily));
    _itemImgGenerily->setPosition(ccp(125, 230));
    
    _itemImgDifficulty = CCMenuItemImage::create("kuang_03.png", "kuang_03.png", this, menu_selector(OptionLayer::selectDifficulty));
    _itemImgDifficulty->setPosition(ccp(205, 230));
    
    this->selectDisplay();
    this->selectMusic();
    this->selectSound();
    
    //返回
    //    _itemImgBack = CCMenuItemImage::create("yes_01.png", "yes_01.png", this, menu_selector(OptionView::selectBack));
    //    _itemImgBack->setPosition(ccp(250, 100));
    
    CCLabelTTF *labBack = CCLabelTTF::create("返回", "Arial", 23);
    _itemImgBack = CCMenuItemLabel::create(labBack, this, menu_selector(OptionLayer::selectBack));
    _itemImgBack->setPosition(ccp(240, 60));
    
    //菜单
    _menuOption = CCMenu::create(_itemImgEasy, _itemImgGenerily, _itemImgDifficulty, _itemImgBack, itemImgMusic, itemImgSound, NULL);
    _menuOption->setPosition(CCPointZero);
    this->addChild(_menuOption, 0);
}

#pragma mark - 选择框
void OptionLayer::selectEasy()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("selectValue", 1);
    this->selectDisplay();
}

void OptionLayer::selectGenerily()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("selectValue", 2);
    this->selectDisplay();
}

void OptionLayer::selectDifficulty()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("selectValue", 3);
    this->selectDisplay();
}

#pragma mark - 返回选择框
void OptionLayer::selectBack()
{
    LoadingView *_loadingView = LoadingView::create();
    DIRECTOR->replaceScene(_loadingView);
    
    int iSelectSound = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectSound");
    if (iSelectSound == 2) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("selectSound", 3);
    }
    
    int iSelectMusic = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectMusic");
    if (iSelectMusic == 2) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("selectMusic", 3);
    }
}

#pragma mark - 选择框显示
void OptionLayer::selectDisplay()
{
    int iSelectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
    USERFLUSH;
    
    //难度选择框
    switch (iSelectValue) {
        case 1:
            _selectSprite->setPosition(_itemImgEasy->getPosition());
            break;
            
        case 2:
            _selectSprite->setPosition(_itemImgGenerily->getPosition());
            break;
            
        case 3:
            _selectSprite->setPosition(_itemImgDifficulty->getPosition());
            break;
            
        default:
            break;
    }
    
    this->jinggao();
}

//音乐的选择操作
void OptionLayer::selectMusicDefault()
{
    int iSelectMusic = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectMusic");
    USERFLUSH;
    if (iSelectMusic == 1) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("selectMusic", 2);
    }
    else {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("selectMusic", 1);
    }
    
    this->selectMusic();
}

//音效的选择操作
void OptionLayer::selectSoundDefault()
{
    int iSelectSound = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectSound");
    USERFLUSH;
    if (iSelectSound == 1) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("selectSound", 2);
    }
    else {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("selectSound", 1);
    }
    
    this->selectSound();
}

//音乐的选择操作
void OptionLayer::selectMusic()
{
    int iSelectMusic = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectMusic");
    
    switch (iSelectMusic) {
        case 1:
            _selectMusic->setPosition(ccp(90, 350));
            break;
            
        case 2:
            _selectMusic->setPosition(ccp(90, 600));
            break;
            
        default:
            break;
    }
}

//音效的选择操作
void OptionLayer::selectSound()
{
    int iSelectSound = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectSound");
    
    switch (iSelectSound) {
        case 1:
            _selectSound->setPosition(ccp(90, 315));
            break;
            
        case 2:
            _selectSound->setPosition(ccp(90, 600));
            break;
            
        default:
            break;
    }
}

//选择难度后的提示
void OptionLayer::jinggao()
{
    int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
    CCString *str = CCString::create("");
    if (iSeclectValue == 3) {
        str = CCString::create("准备好菊花绽放");
    }
    else if (iSeclectValue == 1) {
        str = CCString::create("娱乐才刚刚开始");
    }
    else {
        str = CCString::create("少儿不宜");
    }
    
    _tishi = CCLabelTTF::create(str->getCString(), "Arial", 40);
    _tishi->setPosition(ccp(160, 120));
    this->addChild(_tishi);
    
    CCActionInterval *fadIn = CCFadeIn::create(3);
    CCActionInterval *fadOut = CCFadeOut::create(1);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(OptionLayer::removeLab));
    CCFiniteTimeAction *seq = CCSequence::create(fadIn, fadOut, actionMoveDone, NULL);
    
    _tishi->runAction(seq);
}

void OptionLayer::removeLab()
{
    this->removeChild(_tishi, true);
}


































