//
//  LoadingView.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-3.
//
//

#ifndef _______LoadingView__
#define _______LoadingView__

#include <iostream>
#include "OptionView.h"
#include "RecordView.h"
#include "GameScene.h"
#include "cocos2d.h"
using namespace cocos2d;
class LoadingView:public CCScene
{
public:
    CREATE_FUNC(LoadingView);
    
    LoadingView();
    ~LoadingView();
    
    virtual bool init();
    
    void initBackground();//初始化背景
    void initMenus();//初始化菜单选项
    void startGame();//开始游戏
    void exitGame();//退出游戏
    void optionGame();//进入游戏选项
    void recordGame();//进入游戏分数排行榜
};

#endif /* defined(_______LoadingView__) */
