//
//  ___AppDelegate.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-6-27.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "GameScene.h"
#include "LoadingView.h"
using namespace std;

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //----------------------------------------------------------------------------
    
    bool _isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
    if (_isBeginner)
    {
        //初始化时先重置
//        this->reset();
        //保存初始化之后的数据
//        this->flush();
        //初始化一次之后，只要不重置就用再初始化了
//        this->setBeginner(false);
//        CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", false);
    }
    else
    {
        this->flush();//重置参数
        CCUD->setBoolForKey("beginner", true);//决定是否重置的参数
        USERFLUSH;
    }
    
    //----------------------------------------------------------------------------

    // create a scene. it's an autorelease object
//    CCScene *pScene = GameScene::create();
    CCScene *pScene = LoadingView::create();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

//重置参数
void AppDelegate::flush()
{
    CCUD->setIntegerForKey("selectValue", 2);
    CCUD->setIntegerForKey("selectSound", 2);
    CCUD->setIntegerForKey("selectMusic", 2);
    
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
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
