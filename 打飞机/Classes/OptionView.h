//
//  OptionView.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-3.
//
//

#ifndef _______OptionView__
#define _______OptionView__

#include <iostream>
#include "LoadingView.h"
#include "OptionLayer.h"
#include "cocos2d.h"
using namespace cocos2d;
class OptionView:public CCScene
{
public:
    CREATE_FUNC(OptionView);
    
    OptionView();
    ~OptionView();
    
    CC_SYNTHESIZE_RETAIN(OptionLayer *, _optionLayer, OptionLayer);
    
    virtual bool init();
};

#endif /* defined(_______OptionView__) */
