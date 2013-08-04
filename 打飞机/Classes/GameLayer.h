//
//  GameLayer.h
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#ifndef _______GameLayer__
#define _______GameLayer__

#include <iostream>
#include "HeroOne.h"
#include "DevilOne.h"
#include "cocos2d.h"
#include "DevilBoss.h"
using namespace cocos2d;
class GameLayer:public CCLayer
{
public:
    CREATE_FUNC(GameLayer);
    
    GameLayer();
    ~GameLayer();
    
    HeroOne *_hero;
    DevilOne *_devilOne;
    CC_SYNTHESIZE(CCArray *, _devilOneArray, DevilOneArray);//tag=3
    CC_SYNTHESIZE(CCArray *, _heroOneArray, HeroOneArray);//tag=4
    CC_SYNTHESIZE(CCArray *, _heroBulletArray, HeroBulletArray);//tag=1
    CC_SYNTHESIZE(CCArray *, _devilBulletArray, DevilBulletArray);//tag=2
    CC_SYNTHESIZE(CCArray *, _bossBulletArray, BossBulletArray);//tag=5
    CC_SYNTHESIZE(CCArray *, _bossArray, BossArray);//tag=6
    CC_SYNTHESIZE(CCSprite *, _spHongXue, SpHongXue);
    CC_SYNTHESIZE(CCSprite *, _spHongXueBoss, SpHongXueBoss);
    CC_SYNTHESIZE(CCSprite *, _spKong, SpKong);
    CC_SYNTHESIZE(CCSprite *, _spKongBoss, SpKongBoss);
    CC_SYNTHESIZE(DevilBoss *, _boss, Boss);
    CC_SYNTHESIZE(CCLabelTTF *, _labScore, LabScore);
    CC_SYNTHESIZE(CCLabelTTF *, _labxue, Labxue);
    CC_SYNTHESIZE(CCLabelTTF *, _lScore, LScore);
    CC_SYNTHESIZE(CCLabelTTF *, _leavel, Leavel);
    
    //游戏菜单选项
    CC_SYNTHESIZE(CCMenuItemImage *, _pauseItemImage, PauseItemImage);
    CC_SYNTHESIZE(CCMenu *, _gameMenu, GameMenu);
    
    cocos2d::CCSpriteBatchNode *_actors;
    int iDevilOneNum;
    int iDevilNum;
    int iBossNum;
    int iBossXUE;
    int iBossScore;
    
    bool init();
    
    void initMap();
    void initHero();
    void initHeroBullet();
    void updataHeroPoint(CCPoint _point);//更新主角的移动位置
    void initDevilOne();
    void initDevilTwo();
    void initBoss();
    void bossMove();
    void initBossBulletOne();
    void initBossBulletTwo();
    void initBossBulletThree();
    void initDevilBullet();
    float computeStrike(float _fPower, float _fHp);
    void computeScore(float _fDevilScore);
    void initGameOverLayer();
    void checkGameOver();
    void checkGameWin();
    void checkGameLose();
    void spriteFadOut(CCSprite *_sp);
    
    void initLeavel();
    
    //动态显示分数
    void initScore();
    void displayScore(float fScore, DevilOne *_devil);
    void removeScore();
    
    //菜单
    void initTitleMessage();
    void initMenu();
    void menuActions();
    void menuFadIn();
    void menuFadOut();
    void gamePause();
    void gameContinue();
    
    //血条移动
    void moveHP(float fHp);
    void moveBossHP(float fHp);
    
    //界面切换
    void selectBack();
    void restratGame();
    
    //移动：：参数，当前点，目标点，速度，被执行精灵
    void spriteMove(CCPoint _presentPoint, CCPoint _moveToPoint, float _speed, CCSprite *_sprite);
    //计算移动时间
    float spriteMoveTime(CCPoint _presentPoint, CCPoint _moveToPoint, float _speed);
    //到目标位置的距离
    CCPoint spriteMoveLength(CCPoint _presentPoint, CCPoint _moveToPoint);
    //计算目标移动位置
    CCPoint spriteMoveDestination(CCPoint _presentPoint, CCPoint _moveToPoint);
    
    void spriteMoveFinished(CCNode *sender);//删除对象
    
    //触摸事件
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    //碰撞事件
    void beginCheckStrike();//开始检测碰撞
    void heroStrikeDevil();//怪物碰撞英雄
    void heroBulletStrikeDevil();//英雄子弹碰撞怪物
    void heroStrikeDevilBullet();//怪物子弹碰撞英雄
    void heroStrikeBoss();//BOSS碰撞英雄
    void heroBulletStrikeBoss();//BOSS碰撞英雄子弹
    void heroStrikeBossBulet();//Boss子弹碰撞英雄
    bool endCheckStrike(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo);//检测碰撞是否发生
};

#endif /* defined(_______GameLayer__) */
