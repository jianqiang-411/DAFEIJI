//
//  RecordView.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-3.
//
//

#ifndef _______RecordView__
#define _______RecordView__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
class RecordView:public CCScene
{
public:
    CREATE_FUNC(RecordView);
    
    RecordView();
    ~RecordView();
    
    CC_SYNTHESIZE(CCMenuItemImage *, _itemImgClear, ItemImgClear);
    CC_SYNTHESIZE(CCLabelTTF *, _labFirstScore, LabFirstScore);
    CC_SYNTHESIZE(CCLabelTTF *, _labSecondScore, LabSecondScore);
    CC_SYNTHESIZE(CCLabelTTF *, _labThirdScore, LabThirdScore);
    CC_SYNTHESIZE(CCLabelTTF *, _labForthScore, LabForthScore);
    CC_SYNTHESIZE(CCLabelTTF *, _labFifthScore, LabFifthScore);
    CC_SYNTHESIZE(CCLabelTTF *, _labFirstNum, LabFirstNum);
    CC_SYNTHESIZE(CCLabelTTF *, _labSecondNum, LabSecondNum);
    CC_SYNTHESIZE(CCLabelTTF *, _labThirdNum, LabThirdNum);
    CC_SYNTHESIZE(CCLabelTTF *, _labForthNum, LabForthNum);
    CC_SYNTHESIZE(CCLabelTTF *, _labFifthNum, LabFifthNum);
    CC_SYNTHESIZE(CCMenu *, _menu, Menu);
    CC_SYNTHESIZE(CCMenu *, _menuYESorNO, MenuYESorNO);
    CC_SYNTHESIZE(CCLabelTTF *, _labAlock, LabAlock);
    CC_SYNTHESIZE(CCSprite *, _spriteBackground, SpriteBackground);
    
    int i;
    
    virtual bool init();
    
    void recordBackground();
    void recordMenuCreate();
    void initClear();
    void clearSpriteAction();
    void clearButnCreate();
    void selectBack();
    void selectClear();
    void yesORno();
    void selectNO();
    void scoreUpdata();
    void scoreDisplay();
    void displayFirst();
    void displaySecond();
    void displayThird();
    void displayForth();
    void displayFifth();
};

#endif /* defined(_______RecordView__) */
