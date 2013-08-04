//
//  OptionView.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-3.
//
//

#include "OptionView.h"
#include "LoadingView.h"
#include "Defines.h"
using namespace cocos2d;
OptionView::OptionView()
{
    _optionLayer = NULL;
}

OptionView::~OptionView()
{
    
}

bool OptionView::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());

        _optionLayer = OptionLayer::create();
        this->addChild(_optionLayer);
        
        pRet = true;
    } while(0);
    
    return pRet;
}






































