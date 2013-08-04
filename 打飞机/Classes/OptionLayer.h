//
//  OptionLayer.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-4.
//
//

#ifndef _______OptionLayer__
#define _______OptionLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class OptionLayer:public CCLayer
{
public:
    CREATE_FUNC(OptionLayer);
    
    CC_SYNTHESIZE(CCMenuItemImage *, _itemImgEasy, ItemImgEasy);//简单选项框
    CC_SYNTHESIZE(CCMenuItemImage *, _itemImgGenerily, ItemImgGenerily);//普通选项框
    CC_SYNTHESIZE(CCMenuItemImage *, _itemImgDifficulty, ItemImgDifficulty);//困难选项框
    CC_SYNTHESIZE(CCMenuItemLabel *, _itemImgBack, ItemImgBack);//返回键单元
    CC_SYNTHESIZE_RETAIN(CCMenu *, _menuOption, MenuOption);//菜单
    CC_SYNTHESIZE_RETAIN(CCSprite *, _selectSprite, SelectSprite);//选项框单元
    CC_SYNTHESIZE_RETAIN(CCSprite *, _selectMusic, SelectMusic);
    CC_SYNTHESIZE_RETAIN(CCSprite *, _selectSound, SelectSound);
    CC_SYNTHESIZE(CCLabelTTF *, _tishi, Tishi);
    
    OptionLayer();
    
    bool init();
    
    void initSelect();
    void optionViewCreate();
    void optionBackground();
    void optionMenu();
    void selectEasy();
    void selectGenerily();
    void selectDifficulty();
    void selectBack();
    void selectDisplay();
    void selectMusic();
    void selectSound();
    void selectMusicDefault();
    void selectSoundDefault();
    void jinggao();
    void removeLab();
};

#endif /* defined(_______OptionLayer__) */
