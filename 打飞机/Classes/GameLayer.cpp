//
//  GameLayer.cpp
//  打飞机
//
//  Created by 阚 庭树 on 13-7-8.
//
//

#include "GameLayer.h"
#include "Defines.h"
#include "GameOverLayer.h"
#include "HeroBullet.h"
#include "DevilBullet.h"
#include "DevilTwo.h"
#include "LoadingView.h"
#include "GameScene.h"
#include "DevilBoss.h"
#include "BossBulletOne.h"
#include "BossBulletTwo.h"
using namespace cocos2d;
GameLayer::GameLayer()
{
    _hero = NULL;
    _devilOne = NULL;
    _boss = NULL;
    _devilOneArray = NULL;
    _heroOneArray = NULL;
    _heroBulletArray = NULL;
    _devilBulletArray = NULL;
    _bossArray = NULL;
    _bossBulletArray = NULL;
    iDevilOneNum = 0;
    iBossNum = 0;
    iBossXUE = 0;
    iDevilNum = 0;
    
    _labScore = NULL;
    _lScore = NULL;
    _labxue = NULL;
    _spHongXue = NULL;
    _spHongXueBoss = NULL;
    _spKong = NULL;
    
    _leavel = NULL;
}

GameLayer::~GameLayer()
{
    
}

bool GameLayer::init()
{
    bool pRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ziyuan.plist");
        _actors = CCSpriteBatchNode::create("ziyuan.pvr.ccz");
        _actors->getTexture()->setAliasTexParameters();
        this->addChild(_actors, 1);
        
        _devilOneArray = CCArray::create();
        _devilOneArray->retain();
        _heroOneArray = CCArray::create();
        _heroOneArray->retain();
        _heroBulletArray = CCArray::create();
        _heroBulletArray->retain();
        _devilBulletArray = CCArray::create();
        _devilBulletArray->retain();
        _bossBulletArray = CCArray::create();
        _bossBulletArray->retain();
        _bossArray = CCArray::create();
        _bossArray->retain();
        
        
        this->initMap();
        this->initHero();
        this->initTitleMessage();
        this->initScore();
        
        //注册单点触摸事件
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        //定时创建怪物
        this->schedule(schedule_selector(GameLayer::initDevilOne), 1.0);
        //定时创建怪物
        this->schedule(schedule_selector(GameLayer::initDevilTwo), 5.0);
        //定时监测碰撞事件
        this->schedule(schedule_selector(GameLayer::beginCheckStrike));
        //主角定时发射子弹
//        this->schedule(schedule_selector(GameLayer::initHeroBullet), 0.3);
        
        this->initLeavel();
        
        pRet = true;
    } while(0);
    
    return pRet;
}

void GameLayer::initLeavel()
{
    //怪物定时发射子弹,英雄子弹定时，关卡显示
    _leavel = CCLabelTTF::create("", "Arial", 35);
    _leavel->setPosition(ccp(160, 240));
    this->addChild(_leavel, 5);
    
    int iGameOverTemp = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameOverTemp");
    
    iDevilNum = CCUD->getIntegerForKey("devilnum");     //控制怪物数量和boss出现时间
    int iSeclectValue = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectValue");
    if (iSeclectValue == 3) {
        this->schedule(schedule_selector(GameLayer::initDevilBullet), 0.5);
        this->schedule(schedule_selector(GameLayer::initHeroBullet), 0.2);
        
        iBossScore = 30;
        if (iGameOverTemp == 1) {
            int scoreNew = CCUD->getIntegerForKey("scoreNew") + 4000;
            CCUD->setIntegerForKey("scoreNew", scoreNew);
            iDevilNum = iDevilNum + DEVILNUM;
            CCUD->setIntegerForKey("devilnum", iDevilNum);
        }
        else {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreNew", 2000);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumNew", 0);
        }
        
        
    }
    else if (iSeclectValue == 1) {
        this->schedule(schedule_selector(GameLayer::initDevilBullet), 1);
        this->schedule(schedule_selector(GameLayer::initHeroBullet), 0.6);
        
        iBossScore = 10;
        
        if (iGameOverTemp == 1) {
            int scoreNew = CCUD->getIntegerForKey("scoreNew") + 1000;
            CCUD->setIntegerForKey("scoreNew", scoreNew);
            iDevilNum = iDevilNum + DEVILNUM;
            CCUD->setIntegerForKey("devilnum", iDevilNum);
        }
        else {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreNew", 0);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumNew", 0);
        }
    }
    else {
        this->schedule(schedule_selector(GameLayer::initDevilBullet), 0.7);
        this->schedule(schedule_selector(GameLayer::initHeroBullet), 0.4);
        
        iBossScore = 20;
        
        if (iGameOverTemp == 1) {
            int scoreNew = CCUD->getIntegerForKey("scoreNew") + 2000;
            CCUD->setIntegerForKey("scoreNew", scoreNew);
            iDevilNum = iDevilNum + DEVILNUM;
            CCUD->setIntegerForKey("devilnum", iDevilNum);
        }
        else {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreNew", 1000);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumNew", 0);
        }
    }
    
    int iNum = iDevilNum / DEVILNUM;
    CCString *str = CCString::createWithFormat("第%i关", iNum);
    _leavel->setString(str->getCString());
    
    CCActionInterval *fadIn = CCFadeIn::create(1);
    CCActionInterval *fadOut = CCFadeOut::create(2);
    CCFiniteTimeAction *seq = CCSequence::create(fadIn, fadOut, NULL);
    _leavel->runAction(seq);
    
    iDevilNum = iDevilNum + 5;
    this->schedule(schedule_selector(GameLayer::initBoss), iDevilNum);//怪物数量加上5秒
}


#pragma mark - 地图
/*************************************************************************************
 函数：initMap()
 简介：初始化地图
 功能：
 
 
 *************************************************************************************/
void GameLayer::initMap()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *_map = CCSprite::create("background.png");
    _map->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(_map, 0);
}


#pragma mark - 英雄
/*************************************************************************************
 函数：initDevil()
      initHeroBullet()
      updataHeroPoint(CCPoint _point)
 简介：1 创建英雄
      2 创建英雄子弹
      3 更新英雄位置
 功能：
 *************************************************************************************/
void GameLayer::initHero()
{
    _hero = HeroOne::create();
    _hero->setPosition(ccp(160, 40));
    _hero->setTag(4);
    this->addChild(_hero, 1);
    _heroOneArray->addObject(_hero);
    
}

void GameLayer::updataHeroPoint(CCPoint _point)
{
    if (_point.y > 400) {
        _point.y = 400;
    }
    _hero->setPosition(_point);
}

void GameLayer::initHeroBullet()
{
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_heroOneArray, pObject) {
        HeroOne *hero = (HeroOne *) pObject;
        HeroBullet *heroBullet = HeroBullet::create();
        heroBullet->setPosition(ccp(hero->getPosition().x, hero->getPosition().y + 30));
        
        HeroBullet *heroBullet2 = HeroBullet::create();
        heroBullet2->setPosition(ccp(hero->getPosition().x, hero->getPosition().y - 30));
        
        heroBullet->setTag(1);
        this->addChild(heroBullet, 1);
        _heroBulletArray->addObject(heroBullet);
        
        heroBullet2->setTag(1);
        this->addChild(heroBullet2, 1);
        _heroBulletArray->addObject(heroBullet2);
        
        CCPoint point = CCPointMake(heroBullet->getPosition().x, heroBullet->getPosition().y + 500);
        CCPoint point2 = CCPointMake(heroBullet2->getPosition().x, heroBullet2->getPosition().y - 500);
        this->spriteMove(heroBullet->getPosition(), point, heroBullet->getFHeroBulletSpeed(), heroBullet);
        this->spriteMove(heroBullet2->getPosition(), point2, heroBullet2->getFHeroBulletSpeed(), heroBullet2);
    }
}

void GameLayer::spriteFadOut(CCSprite *_sp)
{
    CCActionInterval *fadOut = CCFadeOut::create(0.1);
    _sp->runAction(fadOut);
}

#pragma mark - 怪物
/*************************************************************************************
 函数：initDevil()
 initDevilBullet()
 简介：1 创建怪物
 2 创建怪物子弹
 功能：
 
 
 *************************************************************************************/
void GameLayer::initDevilOne()
{
    if (iDevilOneNum < DEVILNUM) {
        _devilOne = DevilOne::create();
        
        //产生一个x轴的随机位置
        int minX = _devilOne->getContentSize().width / 2;
        int maxX = SCREEN.width - minX;
        int rangeX = maxX - minX;
        int randX = (rand() % rangeX) + minX;
        
        _devilOne->setPosition(ccp(randX, SCREEN.height + _devilOne->getContentSize().height / 2));
        
        _devilOne->setTag(3);
        this->addChild(_devilOne, 1);
        _devilOneArray->addObject(_devilOne);
        
        CCPoint point = CCPointMake(_devilOne->getPosition().x, 0 - _devilOne->getContentSize().height / 2);
        this->spriteMove(_devilOne->getPosition(), point, _devilOne->getFDevilSpeed(), _devilOne);
    }
    
//    if (iDevilOneNum == DEVILNUM) {
//        this->initBoss();
//    }
    
    iDevilOneNum++;
}

void GameLayer::initDevilTwo()
{
    if (iDevilOneNum < DEVILNUM) {
        DevilTwo *devilTwo = DevilTwo::create();
        
        //产生一个x轴的随机位置
        int minX = devilTwo->getContentSize().width / 2;
        int maxX = SCREEN.width - minX;
        int rangeX = maxX - minX;
        int randX = (rand() % rangeX) + minX;
        
        devilTwo->setPosition(ccp(randX, SCREEN.height + devilTwo->getContentSize().height / 2));
        devilTwo->setTag(3);
        
        this->addChild(devilTwo, 1);
        _devilOneArray->addObject(devilTwo);
        
        this->spriteMove(devilTwo->getPosition(), _hero->getPosition(), devilTwo->getFDevilSpeed(), devilTwo);
    }
}

void GameLayer::initBoss()
{
//    this->unschedule(schedule_selector(GameLayer::initDevilOne));
//    this->unschedule(schedule_selector(GameLayer::initDevilTwo));
//    this->unschedule(schedule_selector(GameLayer::initDevilBullet));
    
    if (iBossNum == 0) {
        _boss = DevilBoss::create();
        _boss->setPosition(ccp(SCREEN.width / 2, _boss->getContentSize().height / 2 + SCREEN.height));
        this->addChild(_boss, 1);
        _boss->setTag(6);
        _bossArray->addObject(_boss);
        
        CCPoint point = CCPointMake(_boss->getPosition().x, SCREEN.height - _boss->getContentSize().height / 2 - 30);
        float moveTime = this->spriteMoveTime(_boss->getPosition(), point, _boss->getFDevilSpeed());
        CCMoveTo *moveTo1 = CCMoveTo::create(moveTime, point);
        
        CCPoint point1 = CCPointMake(_boss->getContentSize().width / 2, point.y);
        moveTime = this->spriteMoveTime(point, point1, _boss->getFDevilSpeed());
        CCMoveTo *moveTo2 = CCMoveTo::create(moveTime, point1);
        
        CCCallFuncN *actionDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::bossMove));
        CCFiniteTimeAction *seq = CCSequence::create(moveTo1, moveTo2, actionDone, NULL);
        _boss->runAction(seq);
        
        this->schedule(schedule_selector(GameLayer::initBossBulletOne), 1);
        this->schedule(schedule_selector(GameLayer::initBossBulletTwo), 2);
        this->schedule(schedule_selector(GameLayer::initBossBulletThree), 3);
        
        iBossXUE = _boss->getFDevilHp();
    }
    iBossNum++;
    
}

void GameLayer::initDevilBullet()
{
    if (_devilOneArray->count() != 0) {
        CCObject *pob = NULL;
        CCARRAY_FOREACH(_devilOneArray, pob) {
            CCSprite *devil = (CCSprite *) pob;
            if (devil->getPosition().y > SCREEN.height / 3) {
                DevilBullet *devilBullet = DevilBullet::create();
                devilBullet->setPosition(ccp(devil->getPosition().x, devil->getPosition().y));
                
                devilBullet->setTag(2);
                this->addChild(devilBullet, 1);
                _devilBulletArray->addObject(devilBullet);
                
                
                CCPoint destinationPoint = this->spriteMoveDestination(devilBullet->getPosition(), _hero->getPosition());
                this->spriteMove(devilBullet->getPosition(), destinationPoint, devilBullet->getFDevilBulletSpeed(), devilBullet);
            }
            
        }
        
    }

}

void GameLayer::initBossBulletOne()
{
    CCObject *pObject = NULL;
    if (_bossArray != 0 && _bossArray != NULL) {
        CCARRAY_FOREACH(_bossArray, pObject) {
            DevilBoss *boss = (DevilBoss *) pObject;
            
            BossBulletOne  *bullet1 = BossBulletOne::create();
            bullet1->setPosition(boss->getPosition());
            this->addChild(bullet1, 2);
            bullet1->setTag(5);
            _bossBulletArray->addObject(bullet1);
            
            BossBulletOne  *bullet2 = BossBulletOne::create();
            bullet2->setPosition(ccp(boss->getPosition().x, boss->getPosition().y));
            this->addChild(bullet2, 2);
            bullet2->setTag(5);
            _bossBulletArray->addObject(bullet2);
            
            BossBulletOne  *bullet3 = BossBulletOne::create();
            bullet3->setPosition(ccp(boss->getPosition().x, boss->getPosition().y));
            this->addChild(bullet3, 2);
            bullet3->setTag(5);
            _bossBulletArray->addObject(bullet3);
            
            BossBulletOne  *bullet4 = BossBulletOne::create();
            bullet4->setPosition(ccp(boss->getPosition().x, boss->getPosition().y));
            this->addChild(bullet4, 2);
            bullet4->setTag(5);
            _bossBulletArray->addObject(bullet4);
            
            BossBulletOne  *bullet5 = BossBulletOne::create();
            bullet5->setPosition(ccp(boss->getPosition().x, boss->getPosition().y));
            this->addChild(bullet5, 2);
            bullet5->setTag(5);
            _bossBulletArray->addObject(bullet5);
            
            BossBulletOne  *bullet6 = BossBulletOne::create();
            bullet6->setPosition(ccp(boss->getPosition().x, boss->getPosition().y));
            this->addChild(bullet6, 2);
            bullet6->setTag(5);
            _bossBulletArray->addObject(bullet6);
            
            BossBulletOne  *bullet7 = BossBulletOne::create();
            bullet7->setPosition(ccp(boss->getPosition().x, boss->getPosition().y));
            this->addChild(bullet7, 2);
            bullet7->setTag(5);
            _bossBulletArray->addObject(bullet7);
            
            CCPoint point1 = CCPointMake(bullet1->getPosition().x - 150, bullet1->getPosition().y - 400);
            CCPoint point2 = CCPointMake(bullet2->getPosition().x - 100, bullet2->getPosition().y - 400);
            CCPoint point3 = CCPointMake(bullet3->getPosition().x - 50, bullet3->getPosition().y - 400);
            CCPoint point4 = CCPointMake(bullet4->getPosition().x, bullet4->getPosition().y - 400);
            CCPoint point5 = CCPointMake(bullet5->getPosition().x + 50, bullet5->getPosition().y - 400);
            CCPoint point6 = CCPointMake(bullet6->getPosition().x + 100, bullet6->getPosition().y - 400);
            CCPoint point7 = CCPointMake(bullet7->getPosition().x + 150, bullet7->getPosition().y - 400);
            
            this->spriteMove(bullet1->getPosition(), point1, bullet1->getFDevilBulletSpeed(), bullet1);
            this->spriteMove(bullet2->getPosition(), point2, bullet2->getFDevilBulletSpeed(), bullet2);
            this->spriteMove(bullet3->getPosition(), point3, bullet3->getFDevilBulletSpeed(), bullet3);
            this->spriteMove(bullet4->getPosition(), point4, bullet4->getFDevilBulletSpeed(), bullet4);
            this->spriteMove(bullet5->getPosition(), point5, bullet5->getFDevilBulletSpeed(), bullet5);
            this->spriteMove(bullet6->getPosition(), point6, bullet6->getFDevilBulletSpeed(), bullet6);
            this->spriteMove(bullet7->getPosition(), point7, bullet7->getFDevilBulletSpeed(), bullet7);
        }
    }
}

void GameLayer::initBossBulletTwo()
{
    if (_bossArray != 0 && _bossArray != NULL) {
        CCObject *pObject = NULL;
        CCARRAY_FOREACH(_bossArray, pObject) {
            DevilBoss *boss = (DevilBoss *) pObject;
            
            BossBulletOne  *bullet1 = BossBulletOne::create();
            bullet1->setPosition(ccp(boss->getPosition().x - 40, boss->getPosition().y - 30));
            this->addChild(bullet1, 2);
            bullet1->setTag(5);
            _bossBulletArray->addObject(bullet1);
            
            BossBulletOne  *bullet2 = BossBulletOne::create();
            bullet2->setPosition(ccp(boss->getPosition().x + 40, boss->getPosition().y - 30));
            this->addChild(bullet2, 2);
            bullet2->setTag(5);
            _bossBulletArray->addObject(bullet2);
            
            CCPoint point1 = CCPointMake(bullet1->getPosition().x, bullet1->getPosition().y - 500);
            CCPoint point2 = CCPointMake(bullet2->getPosition().x, bullet2->getPosition().y - 500);
            
            this->spriteMove(bullet1->getPosition(), point1, bullet1->getFDevilBulletSpeed(), bullet1);
            this->spriteMove(bullet2->getPosition(), point2, bullet2->getFDevilBulletSpeed(), bullet2);
        }
    }
}

void GameLayer::initBossBulletThree()
{
    if (_bossArray != 0 && _bossArray != NULL) {
        CCObject *pObject = NULL;
        CCARRAY_FOREACH(_bossArray, pObject) {
            DevilBoss *boss = (DevilBoss *) pObject;
            
            BossBulletOne  *bullet1 = BossBulletOne::create();
            bullet1->setPosition(ccp(boss->getPosition().x - 70, boss->getPosition().y + 15));
            this->addChild(bullet1, 2);
            bullet1->setTag(5);
            _bossBulletArray->addObject(bullet1);
            
            BossBulletOne  *bullet2 = BossBulletOne::create();
            bullet2->setPosition(ccp(boss->getPosition().x - 70, boss->getPosition().y - 3));
            this->addChild(bullet2, 2);
            bullet2->setTag(5);
            _bossBulletArray->addObject(bullet2);
            
            BossBulletOne  *bullet3 = BossBulletOne::create();
            bullet3->setPosition(ccp(boss->getPosition().x - 70, boss->getPosition().y - 30));
            this->addChild(bullet3, 2);
            bullet3->setTag(5);
            _bossBulletArray->addObject(bullet3);
            
            BossBulletOne  *bullet4 = BossBulletOne::create();
            bullet4->setPosition(ccp(boss->getPosition().x + 70, boss->getPosition().y + 15));
            this->addChild(bullet4, 2);
            bullet4->setTag(5);
            _bossBulletArray->addObject(bullet4);
            
            BossBulletOne  *bullet5 = BossBulletOne::create();
            bullet5->setPosition(ccp(boss->getPosition().x + 70, boss->getPosition().y - 3));
            this->addChild(bullet5, 2);
            bullet5->setTag(5);
            _bossBulletArray->addObject(bullet5);
            
            BossBulletOne  *bullet6 = BossBulletOne::create();
            bullet6->setPosition(ccp(boss->getPosition().x + 70, boss->getPosition().y - 30));
            this->addChild(bullet6, 2);
            bullet6->setTag(5);
            _bossBulletArray->addObject(bullet6);
            
            CCPoint point1 = this->spriteMoveDestination(bullet1->getPosition(), _hero->getPosition());
            CCPoint point2 = this->spriteMoveDestination(bullet2->getPosition(), _hero->getPosition());
            CCPoint point3 = this->spriteMoveDestination(bullet3->getPosition(), _hero->getPosition());
            CCPoint point4 = this->spriteMoveDestination(bullet4->getPosition(), _hero->getPosition());
            CCPoint point5 = this->spriteMoveDestination(bullet5->getPosition(), _hero->getPosition());
            CCPoint point6 = this->spriteMoveDestination(bullet6->getPosition(), _hero->getPosition());
            
            float fSpeed = bullet1->getFDevilBulletSpeed();
            
            this->spriteMove(bullet1->getPosition(), point1, fSpeed, bullet1);
            this->spriteMove(bullet2->getPosition(), point2, fSpeed, bullet2);
            this->spriteMove(bullet3->getPosition(), point3, fSpeed, bullet3);
            this->spriteMove(bullet4->getPosition(), point4, fSpeed, bullet4);
            this->spriteMove(bullet5->getPosition(), point5, fSpeed, bullet5);
            this->spriteMove(bullet6->getPosition(), point6, fSpeed, bullet6);
        }
    }
}



#pragma mark - 怪物移动
/*************************************************************************************
 函数：spriteMove(CCPoint _presentPoint, CCPoint _moveToPoint, float _speed, CCSprite *_sprite)
 CCPoint _presentPoint, CCPoint _moveToPoint, float _speed)
 CCPoint GameLayer::spriteMoveDestination(CCPoint _presentPoint, CCPoint _moveToPoint)
 spriteMoveLength(CCPoint _presentPoint, CCPoint _moveToPoint)
 简介：1 怪物移动
 2 移动时间
 3 移动目标位置
 4 到目标点的距离计算
 功能：
 
 
 *************************************************************************************/
void GameLayer::bossMove()
{
    if (_bossArray != 0 && _bossArray != NULL) {
        CCPoint point = CCPointMake(SCREEN.width - _boss->getContentSize().width / 2, _boss->getPosition().y);
        CCPoint point1 = _boss->getPosition();
        float movetime = this->spriteMoveTime(point1, point, _boss->getFDevilSpeed());
        CCMoveTo *moveTo = CCMoveTo::create(movetime, point);
        CCMoveTo *moveTo1 = CCMoveTo::create(movetime, point1);
        CCCallFuncN *actionDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::bossMove));
        CCFiniteTimeAction *seq = CCSequence::create(moveTo, moveTo1, actionDone, NULL);
        _boss->runAction(seq);
    }
}

void GameLayer::spriteMove(CCPoint _presentPoint, CCPoint _moveToPoint, float _speed, CCSprite *_sprite)
{
    float moveTime = this->spriteMoveTime(_presentPoint, _moveToPoint, _speed);
    
    CCMoveTo *moveTo = CCMoveTo::create(moveTime, _moveToPoint);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::spriteMoveFinished));
    _sprite->runAction(CCSequence::create(moveTo, actionMoveDone, NULL));
}

float GameLayer::spriteMoveTime(CCPoint _presentPoint, CCPoint _moveToPoint, float _speed)
{
    CCPoint lengthPoint = this->spriteMoveLength(_presentPoint, _moveToPoint);
    
    float lengthX = lengthPoint.x;
    float lengthY = lengthPoint.y;
    float moveLength = sqrtf(lengthX * lengthX + lengthY * lengthY);
    float moveTime = moveLength / _speed;
    
    return moveTime;
}

CCPoint GameLayer::spriteMoveLength(CCPoint _presentPoint, CCPoint _moveToPoint)
{
    float moveMaxX = MAX(_presentPoint.x, _moveToPoint.x);
    float moveMinX = MIN(_presentPoint.x, _moveToPoint.x);
    float lengthX = moveMaxX - moveMinX;
    float moveMaxY = MAX(_presentPoint.y, _moveToPoint.y);
    float moveMinY = MIN(_presentPoint.y, _moveToPoint.y);
    float lengthY = moveMaxY - moveMinY;
    
    CCPoint lengthPoint = CCPointMake(lengthX, lengthY);
    
    return lengthPoint;
}

CCPoint GameLayer::spriteMoveDestination(CCPoint _presentPoint, CCPoint _moveToPoint)
{
    CCPoint destinationPoint = _presentPoint;
    CCPoint lengthPoint = this->spriteMoveLength(_presentPoint, _moveToPoint);
    float fLength1 = sqrtf(lengthPoint.x * lengthPoint.x + lengthPoint.y * lengthPoint.y);
    //子弹移动最远距离
    float fLength2 = sqrtf(340 * 340 + 480 * 480);
    float pro = fLength2 / fLength1;
    //以目标位置为物体移动依据的原点
    //如果成立，表明原先物体在x正半轴
    if ((_presentPoint.x > _moveToPoint.x) && (_presentPoint.y == _moveToPoint.y)) {
        destinationPoint.x = -20;
        destinationPoint.y = _presentPoint.y;
    }
    //如果成立，表明原先物体在第一象限
    if ((_presentPoint.x > _moveToPoint.x) && (_presentPoint.y > _moveToPoint.y)) {
        destinationPoint.x = _presentPoint.x - lengthPoint.x * pro;
        destinationPoint.y = _presentPoint.y - lengthPoint.y * pro;
    }
    //如果成立，表明原先物体在y正半轴
    if ((_presentPoint.x == _moveToPoint.x) && (_presentPoint.y > _moveToPoint.y)) {
        destinationPoint.x = _presentPoint.x;
        destinationPoint.y = -20;
    }
    //如果成立，表明原先物体在第二象限
    if ((_presentPoint.x < _moveToPoint.x) && (_presentPoint.y > _moveToPoint.y)) {
        destinationPoint.x = lengthPoint.x * pro + _presentPoint.x;
        destinationPoint.y = _presentPoint.y - lengthPoint.y * pro;
    }
    //如果成立，表明原先物体在x负半轴
    if ((_presentPoint.x < _moveToPoint.x) && (_presentPoint.y == _moveToPoint.y)) {
        destinationPoint.x = 340;
        destinationPoint.y = _presentPoint.y;
    }
    //如果成立，表明原先物体在第三象限
    if ((_presentPoint.x < _moveToPoint.x) && (_presentPoint.y < _moveToPoint.y)) {
        destinationPoint.x = _presentPoint.x + lengthPoint.x * pro;
        destinationPoint.y = _presentPoint.y + lengthPoint.y * pro;
    }
    //如果成立，表明原先物体在y负半轴
    if ((_presentPoint.x == _moveToPoint.x) && (_presentPoint.y < _moveToPoint.y)) {
        destinationPoint.x = _presentPoint.x;
        destinationPoint.y = 500;
    }
    //如果成立，表明原先物体在第四象限
    if ((_presentPoint.x > _moveToPoint.x) && (_presentPoint.y < _moveToPoint.y)) {
        destinationPoint.x = _presentPoint.x - lengthPoint.x * pro;
        destinationPoint.y = _presentPoint.y + lengthPoint.y * pro;
    }
    //如果成立，表明原先物体在原点
    if ((_presentPoint.x == _moveToPoint.x) && (_presentPoint.y == _moveToPoint.y)) {
        destinationPoint.x = _presentPoint.x + 1;
        destinationPoint.y = _presentPoint.y + 1;
    }
    
    return destinationPoint;
}



#pragma mark - 触摸事件执行
/*************************************************************************************
 函数：ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 简介：触摸点的获得，移动和结束
 功能：
 
 
 *************************************************************************************/
bool GameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //获取openGL坐标，原点在左下角
    CCPoint openglPoint = pTouch->getLocation();
//    CCLog("openGL = %f,%f",openglPoint.x,openglPoint.y);
    //    this->updataHeroPoint(openglPoint);
    //获取屏幕坐标，原点在左上角
    //    CCPoint screenPoint = pTouch->getLocationInView();
    //    CCLog("屏幕坐标 = %f,%f",screenPoint.x,screenPoint.y);
    
    //    CCLog("触摸开始------------------");
//    if (openglPoint.x > 280) {
//        if (openglPoint.y > 405) {
//            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//            this->menuActions();
//        }
//    }
//    else {
//        
//    }
    
    return true;
}

void GameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
//    CCPoint openglPoint = pTouch->getLocation();
//    if (openglPoint.x > 280) {
//        if (openglPoint.y > 405) {
//            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//            this->menuActions();
//        }
//    }
//    else {
//        
//    }
    //    CCLog("触摸结束------------------");
}

void GameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //    sleep(2);
    //获得前一个点的坐标
    CCPoint startPoint = pTouch->getPreviousLocation();
    
    //获得当前点的坐标  是按屏幕的坐标获取的就是说以左下角为原点。
    CCPoint endPoint = pTouch->getLocation();
    if (endPoint.x > 280) {
        if (endPoint.y > 405) {
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
            this->menuActions();
        }
    }
    else {
        this->updataHeroPoint(endPoint);
    }
}




#pragma mark - 碰撞事件
/*************************************************************************************
 函数：
 简介：处理碰撞事件
 功能：
 
 
 *************************************************************************************/
//开始检测碰撞事件
void GameLayer::beginCheckStrike()
{
//    if (_heroOneArray->count() != 0 && _devilOneArray->count() != 0) {
        this->heroStrikeDevil();//怪物碰撞英雄
//    }
//    if (_heroBulletArray->count() != 0 && _devilOneArray->count() != 0) {
        this->heroBulletStrikeDevil();//英雄子弹碰撞怪物
//    }
//    if (_heroOneArray->count() != 0 && _devilOneArray->count() != 0) {
        this->heroStrikeDevilBullet();//怪物子弹碰撞英雄,BOSS子弹碰撞英雄
//    }
//    if (_bossArray->count() != 0 && _heroOneArray->count() != 0) {
        this->heroStrikeBoss();//BOSS碰撞英雄
//    }
//    if (_bossArray->count() != 0 && _heroBulletArray->count() != 0) {
        this->heroBulletStrikeBoss();//BOSS碰撞英雄子弹
//    }
//    if (_bossBulletArray->count() != 0 && _heroOneArray->count() != 0) {
        this->heroStrikeBossBulet();//boss子弹碰撞英雄
//    }
//    this->checkGameOver();
//    CCLog("血%i", _hero->getFHeroHp());
//    if (_hero->getFHeroHp() == 0 || _hero == NULL || _heroOneArray->count() == 0) {
//    if (_heroOneArray->count() == 0) {
//        
//        this->unschedule(schedule_selector(GameLayer::beginCheckStrike));
//        this->checkGameLose();
//    }
}

//怪物碰撞英雄
void GameLayer::heroStrikeDevil()
{
    CCObject *heroOneObject = NULL;
    CCObject *devilOneObject = NULL;
    
    CCActionInterval *blink=CCBlink::create(0.2, 2);
    
    bool pRet = false;
    float fHp = 0;
    //--------------------------------英雄碰撞敌机------------------------------------
    CCArray *heroDeleteArray = CCArray::create();
    CCARRAY_FOREACH(_heroOneArray, heroOneObject) {
        HeroOne *heroOne = (HeroOne *) heroOneObject;//得到英雄
        
        CCArray *devilDeleteArray = CCArray::create();
        CCARRAY_FOREACH(_devilOneArray, devilOneObject)
        {
            DevilOne *devilOne = (DevilOne *) devilOneObject;//得到怪物
            pRet = this->endCheckStrike(heroOne->getPosition(), HERORADIUS, devilOne->getPosition(), DEVILRADIUS);//检测是否碰撞
            if (pRet) {
                fHp = this->computeStrike(heroOne->getFHeroPower(), devilOne->getFDevilHp());//计算怪物剩余血量
                if (fHp <= 0) {//如果怪物血量空了
                    this->computeScore(devilOne->getFDevilScore());//怪物被击杀，英雄得分计算
                    this->displayScore(devilOne->getFDevilScore(), devilOne);
                    devilDeleteArray->addObject(devilOne);//怪物等待删除
                }
                else {
                    devilOne->setFDevilHp(fHp);//得到怪物剩余血量
                }
                fHp = this->computeStrike(devilOne->getFDevilPower(), heroOne->getFHeroHp());//计算英雄剩余血量
//                heroOne->runAction(blink);
//                this->moveHP(fHp);//计算显示血量
                if (fHp <= 0) {
                    CCLog("----%f", fHp);
                    fHp = 0;
                    this->moveHP(fHp);//计算显示血量
                    heroDeleteArray->addObject(heroOne);//英雄等待删除
//                    this->checkGameLose();//游戏结束
                }
                else {
                    this->moveHP(fHp);//计算显示血量
                    heroOne->setFHeroHp(fHp);
                }
            }
        }
        //删除怪物
        CCARRAY_FOREACH(devilDeleteArray, devilOneObject) {
            DevilOne *devilOne = (DevilOne *) devilOneObject;
            _devilOneArray->removeObject(devilOne);
            this->removeChild(devilOne, true);
        }
        devilDeleteArray->release();
//        devilDeleteArray = NULL;
    }
    //删除英雄
    CCARRAY_FOREACH(heroDeleteArray, heroOneObject) {
        HeroOne *heroOne = (HeroOne *) heroOneObject;
        _heroOneArray->removeObject(heroOne);
//        this->removeChild(heroOne, true);
        this->spriteFadOut(heroOne);
        this->checkGameLose();//游戏结束
    }
    heroDeleteArray->release();
//    heroDeleteArray = NULL;
}

//英雄子弹碰撞怪物
void GameLayer::heroBulletStrikeDevil()
{
    CCObject *devilOneObject = NULL;
    CCObject *heroBulletObject = NULL;
    
    bool pRet = false;
    float fHp = 0;
    //--------------------------------英雄子弹碰撞敌机------------------------------------
    CCArray *devilDeleteArray = CCArray::create();
    CCARRAY_FOREACH(_devilOneArray, devilOneObject)
    {
        DevilOne *devilOne = (DevilOne *) devilOneObject;//得到怪物
        CCArray *heroBulletDeleteArray = CCArray::create();
        CCARRAY_FOREACH(_heroBulletArray, heroBulletObject) {
            HeroBullet *heroBullet = (HeroBullet *) heroBulletObject;
            pRet = this->endCheckStrike(heroBullet->getPosition(), HEROBULLETRADIUS, devilOne->getPosition(), DEVILRADIUS);//检测是否碰撞
            if (pRet) {
                fHp = this->computeStrike(heroBullet->getFHeroBulletPower(), devilOne->getFDevilHp());
                heroBulletDeleteArray->addObject(heroBullet);
                if (fHp <= 0) {
                    this->computeScore(devilOne->getFDevilScore());//怪物被击杀，英雄得分计算
                    this->displayScore(devilOne->getFDevilScore(), devilOne);
                    devilDeleteArray->addObject(devilOne);//怪物等待删除
                }
                else {
                    devilOne->setFDevilHp(fHp);
                }
            }
        }
        //删除怪物
        CCARRAY_FOREACH(heroBulletDeleteArray, heroBulletObject) {
            HeroBullet *heroBullet = (HeroBullet *) heroBulletObject;
            _heroBulletArray->removeObject(heroBullet);
            this->removeChild(heroBullet, true);
        }
        heroBulletDeleteArray->release();
//        heroBulletDeleteArray = NULL;
    }
    //删除怪物
    CCARRAY_FOREACH(devilDeleteArray, devilOneObject) {
        CCSprite *devilOne = (CCSprite *) devilOneObject;
        _devilOneArray->removeObject(devilOne);
        this->removeChild(devilOne, true);
    }
    devilDeleteArray->release();
//    devilDeleteArray = NULL;
}

//怪物子弹碰撞英雄
void GameLayer::heroStrikeDevilBullet()
{
    CCObject *devilBulletObject = NULL;
    CCObject *heroObject = NULL;
    
    CCActionInterval *blink=CCBlink::create(0.2, 2);
    
    bool pRet = false;
    float fHp = 0;
    //--------------------------------英雄碰撞敌机子弹------------------------------------
    CCArray *heroDeleteArray = CCArray::create();
    CCARRAY_FOREACH(_heroOneArray, heroObject)
    {
        HeroOne *hero = (HeroOne *) heroObject;//得到英雄
        CCArray *devilBulletDeleteArray = CCArray::create();
        CCARRAY_FOREACH(_devilBulletArray, devilBulletObject) {
            DevilBullet *devilBullet = (DevilBullet *) devilBulletObject;
            pRet = this->endCheckStrike(devilBullet->getPosition(), DEVILBULLETRADIUS, hero->getPosition(), HERORADIUS);//检测是否碰撞
            if (pRet) {
//                hero->runAction(blink);
                fHp = this->computeStrike(devilBullet->getFDevilBulletPower(), hero->getFHeroHp());
//                this->moveHP(fHp);//计算英雄显示剩余血量
                devilBulletDeleteArray->addObject(devilBullet);
                if (fHp <= 0) {
                    CCLog("----%f", fHp);
                    fHp = 0;
                    this->moveHP(fHp);//计算英雄显示剩余血量
                    heroDeleteArray->addObject(hero);//英雄等待删除
//                    this->checkGameLose();//游戏结束
                }
                else {
                    this->moveHP(fHp);//计算英雄显示剩余血量
                    hero->setFHeroHp(fHp);
                }
            }
        }
        //删除怪物子弹
        CCARRAY_FOREACH(devilBulletDeleteArray, devilBulletObject) {
            DevilBullet *devilBullet = (DevilBullet *) devilBulletObject;
            _devilBulletArray->removeObject(devilBullet);
            this->removeChild(devilBullet, true);
        }
        devilBulletDeleteArray->release();
//        devilBulletDeleteArray = NULL;
    }
    //删除英雄
    CCARRAY_FOREACH(heroDeleteArray, heroObject) {
        HeroOne *hero = (HeroOne *) heroObject;
        _heroOneArray->removeObject(hero);
//        this->removeChild(hero, true);
        this->spriteFadOut(hero);
        this->checkGameLose();
    }
    heroDeleteArray->release();
//    heroDeleteArray = NULL;
}

void GameLayer::heroStrikeBoss()
{
    bool pRet = false;
    float fHp = 0;
    CCObject *pObject1 = NULL;
    CCObject *pObject2 = NULL;
    
    CCActionInterval *blink=CCBlink::create(0.2, 2);
    
    CCArray *heroToDelete = CCArray::create();
    CCARRAY_FOREACH(_heroOneArray, pObject1) {
        HeroOne *hero = (HeroOne *) pObject1;
        
        CCArray *bossToDelete = CCArray::create();
        CCARRAY_FOREACH(_bossArray, pObject2) {
            DevilBoss *boss = (DevilBoss *) pObject2;
            
            pRet = this->endCheckStrike(boss->getPosition(), BOSSRADIUS, hero->getPosition(), HERORADIUS);
            if (pRet) {
                fHp = this->computeStrike(boss->getFDevilPower(), hero->getFHeroHp());//计算英雄剩余血量
                this->moveHP(fHp);//计算显示血量
                //英雄死亡和受伤计算
                if (fHp <= 0) {
                    CCLog("----%f", fHp);
                    heroToDelete->addObject(hero);
//                    this->checkGameLose();//游戏结束
                }
                else {
                    hero->setFHeroHp(fHp);
//                    hero->runAction(blink);
                }
                
                fHp = this->computeStrike(hero->getFHeroPower(), boss->getFDevilHp());//计算BOSS剩余血量
                this->moveBossHP(fHp);//计算显示血量
                //BOSS死亡和受伤计算
                if (fHp <= 0) {
                    bossToDelete->addObject(boss);
                    this->computeScore(boss->getFDevilScore());//怪物被击杀，英雄得分计算
//                    this->checkGameWin();//游戏结束
                    //            _boss = NULL;
                }
                else {
                    boss->setFDevilHp(fHp);
                }
            }
        }
        //删除boss
        CCARRAY_FOREACH(bossToDelete, pObject2) {
            DevilBoss *boss = (DevilBoss *) pObject2;
            _bossArray->removeObject(boss);
            this->spriteFadOut(boss);
            this->checkGameWin();
//            this->removeChild(boss, true);
//            CCLog("清除---%i", _bossArray->count());
        }
        bossToDelete->release();
//        bossToDelete = NULL;
    }
    //删除英雄
    CCARRAY_FOREACH(heroToDelete, pObject1) {
        HeroOne *hero = (HeroOne *) pObject1;
        _heroOneArray->removeObject(hero);
//        this->removeChild(hero, true);
        this->spriteFadOut(hero);
        this->checkGameLose();
    }
    heroToDelete->release();
//    heroToDelete = NULL;
}

void GameLayer::heroBulletStrikeBoss()
{
    bool pRet = false;
    float fHp = 0;
    CCObject *pObject1 = NULL;
    CCObject *pObject2 = NULL;
    
    CCArray *bossToDelete = CCArray::create();
    CCARRAY_FOREACH(_bossArray, pObject1) {
        DevilBoss *boss = (DevilBoss *) pObject1;
        
        CCArray *bulletToDelete = CCArray::create();
        CCARRAY_FOREACH(_heroBulletArray, pObject2) {
            HeroBullet *bullet = (HeroBullet *) pObject2;
            
            pRet = this->endCheckStrike(bullet->getPosition(), HEROBULLETRADIUS, boss->getPosition(), BOSSRADIUS);
            if (pRet) {
                bulletToDelete->addObject(bullet);
                fHp = this->computeStrike(bullet->getFHeroBulletPower(), boss->getFDevilHp());
                this->moveBossHP(fHp);//计算显示血量
                if (fHp <= 0) {
                    bossToDelete->addObject(boss);
                    this->computeScore(boss->getFDevilScore());//怪物被击杀，英雄得分计算
//                    this->checkGameWin();//游戏结束
                }
                else {
                    boss->setFDevilHp(fHp);
                    
                }
            }
        }
        //删除英雄子弹
        CCARRAY_FOREACH(bulletToDelete, pObject2) {
            HeroBullet *bullet = (HeroBullet *) pObject2;
            _heroBulletArray->removeObject(bullet);
            this->removeChild(bullet, true);
        }
        bulletToDelete->release();
//        bulletToDelete = NULL;
    }
    //删除boss
    CCARRAY_FOREACH(bossToDelete, pObject1) {
        DevilBoss *boss = (DevilBoss *) pObject1;
        _bossArray->removeObject(boss);
        this->spriteFadOut(boss);
        this->checkGameWin();
//        this->removeChild(boss, true);
//        CCLog("清除---%i", _bossArray->count());
    }
    bossToDelete->release();
//    bossToDelete = NULL;
}

void GameLayer::heroStrikeBossBulet()
{
    bool pRet = false;
    float fHp = 0;
    CCObject *pObject1 = NULL;
    CCObject *pObject2 = NULL;
    
    CCActionInterval *blink=CCBlink::create(0.2, 2);
    
    CCArray *heroToDelete = CCArray::create();
    CCARRAY_FOREACH(_heroOneArray, pObject1) {
        HeroOne *hero = (HeroOne *) pObject1;
        
        CCArray *bulletToDelete = CCArray::create();
        CCARRAY_FOREACH(_bossBulletArray, pObject2) {
            BossBulletOne *bullet = (BossBulletOne *) pObject2;
            
            pRet = this->endCheckStrike(hero->getPosition(), HERORADIUS, bullet->getPosition(), DEVILBULLETRADIUS);
            if (pRet) {
                bulletToDelete->addObject(bullet);
                fHp = this->computeStrike(bullet->getFDevilBulletPower(), hero->getFHeroHp());
                this->moveHP(fHp);//计算显示血量
                if (fHp <= 0) {
                    heroToDelete->addObject(hero);
//                    this->checkGameLose();//游戏结束
                }
                else {
                    hero->setFHeroHp(fHp);
                    hero->runAction(blink);
                }
            }
        }
        //删除boss子弹
        CCARRAY_FOREACH(bulletToDelete, pObject2) {
            BossBulletOne *bullet = (BossBulletOne *) pObject2;
            _bossBulletArray->removeObject(bullet);
            this->removeChild(bullet, true);
        }
        bulletToDelete->release();
//        bulletToDelete = NULL;
    }
    //删除英雄
    CCARRAY_FOREACH(heroToDelete, pObject1) {
        HeroOne *hero = (HeroOne *) pObject1;
        _heroOneArray->removeObject(hero);
//        this->removeChild(hero, true);
        this->spriteFadOut(hero);
        this->checkGameLose();
    }
    heroToDelete->release();
//    heroToDelete = NULL;
}

//监测碰撞是否发生
bool GameLayer::endCheckStrike(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo)
{
    float xdif = circlePoint.x - circlePointTwo.x;
    float ydif = circlePoint.y - circlePointTwo.y;
    
    float distance = sqrt(xdif * xdif + ydif * ydif);
    
    if(distance <= radius + radiusTwo)
    {
        return true;
    }
    return false;
}




#pragma mark - 计算
/*************************************************************************************
 函数：computeStrike(float _fPower, float _fHp)
 computeScore()
 简介：伤害计算,分数计算
 功能：
 
 
 *************************************************************************************/
float GameLayer::computeStrike(float _fPower, float _fHp)
{
    float temp = _fHp - _fPower;
    
    return temp;
}

void GameLayer::computeScore(float _fDevilScore)
{
    int iScoreNew = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreNew");
    iScoreNew = iScoreNew + _fDevilScore;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreNew", iScoreNew);
    
    int iDevilNumNew = CCUserDefault::sharedUserDefault()->getIntegerForKey("devilNumNew");
    iDevilNumNew++;
    //    CCLog("------%i,  %i", iScoreNew, iDevilNumNew);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("devilNumNew", iDevilNumNew);
    
    CCString *str = CCString::createWithFormat("得分%i", iScoreNew);
    _lScore->setString(str->getCString());
}




#pragma mark - 显示信息
/*************************************************************************************
 函数：initTitleMessage()
 menuActions()
 menuFadIn()
 gamePause()
 gameContinue()
 简介：显示信息,游戏暂停/继续,菜单的淡入淡出
 功能：
 
 
 *************************************************************************************/
void GameLayer::initTitleMessage()
{
    //控制菜单动画的变量
    CCUserDefault::sharedUserDefault()->setIntegerForKey("pauseAction", 1);
    
    _pauseItemImage = CCMenuItemImage::create("long_stop_05.png", "long_stop_05.png", this, menu_selector(GameLayer::menuActions));
    _pauseItemImage->setPosition( ccp(440, 445) );
    _gameMenu = CCMenu::create(_pauseItemImage, NULL);
    _gameMenu->setPosition( CCPointZero );
    this->addChild(_gameMenu, 6);
    
    //英雄血条
    CCSprite *spTouXiang = CCSprite::create("touxiang_01.png");
    spTouXiang->setPosition(ccp(spTouXiang->getContentSize().width / 2, SCREEN.height - (spTouXiang->getContentSize().height / 2)));
    this->addChild(spTouXiang, 4);
    
    _spKong = CCSprite::create("kongxue_01.png");
    float X = spTouXiang->getContentSize().width + _spKong->getContentSize().width / 2;
    float Y = SCREEN.height - _spKong->getContentSize().height / 2;
    _spKong->setPosition(ccp(X, Y));
    this->addChild(_spKong, 2);
    
    _spHongXue = CCSprite::create("hongxue_01.png");
    _spHongXue->setPosition(_spKong->getPosition());
    this->addChild(_spHongXue, 3);
    
    //英雄血条信息显示
    CCString *str = CCString::createWithFormat("/%i", HEROHP);
    CCLabelTTF *labman = CCLabelTTF::create(str->getCString(), "Arial", 12);
    labman->setColor(ccc3(0, 0, 0));
    labman->setPosition(ccp(_spKong->getPosition().x + 12, _spKong->getPosition().y));
    this->addChild(labman, 4);
    
    _labxue = CCLabelTTF::create(str->getCString(), "Arial", 12);
    _labxue->setColor(ccc3(0, 0, 0));
    _labxue->setPosition(ccp(_spKong->getPosition().x - 12, _spKong->getPosition().y));
    this->addChild(_labxue, 4);
    
    //BOSS血条
    _spKongBoss = CCSprite::create("kongxue_01.png");
    float Xboss = _spKong->getPosition().x;
    float Yboss = _spKong->getPosition().y - _spKongBoss->getContentSize().height - 2;
    _spKongBoss->setPosition(ccp(Xboss, Yboss));
    this->addChild(_spKongBoss, 2);
    
    _spHongXueBoss = CCSprite::create("hongxue_01.png");
    _spHongXueBoss->setPosition(_spKongBoss->getPosition());
    this->addChild(_spHongXueBoss, 3);
    
    CCLabelTTF *labBoss = CCLabelTTF::create("BOSS", "Arial", 12);
    labBoss->setPosition(_spKongBoss->getPosition());
    labBoss->setColor(ccc3(0, 0, 0));
    this->addChild(labBoss, 4);
    
    //分数显示
    int scoreNew = CCUD->getIntegerForKey("scoreNew");
    CCString *str1 = CCString::createWithFormat("得分%i", scoreNew);
    _lScore = CCLabelTTF::create(str1->getCString(), "Arial", 20);
    _lScore->setPosition(ccp(spTouXiang->getPosition().x + 40, SCREEN.height - spTouXiang->getContentSize().height - 20));
    this->addChild(_lScore);
}

void GameLayer::initMenu()
{
    CCLabelTTF *lab_continue = CCLabelTTF::create("CNTINUE", "Arial", 25);
    CCMenuItemLabel *item_continue = CCMenuItemLabel::create(lab_continue, this, menu_selector(GameLayer::menuActions));
    item_continue->setPosition(ccp(195, 390));
    
    CCLabelTTF *lab_option = CCLabelTTF::create("RESTRAT", "Arial", 25);
    CCMenuItemLabel *item_option = CCMenuItemLabel::create(lab_option, this, menu_selector(GameLayer::restratGame));
    item_option->setPosition(ccp(195, 350));
    
    CCLabelTTF *lab_back = CCLabelTTF::create("BACK", "Arial", 25);
    CCMenuItemLabel *item_back = CCMenuItemLabel::create(lab_back, this, menu_selector(GameLayer::selectBack));
    item_back->setPosition(ccp(195, 310));
    
    _gameMenu = CCMenu::create(item_continue, item_option, item_back, NULL);
    _gameMenu->setPosition(CCPointZero);
    this->addChild(_gameMenu, 6);
}

void GameLayer::menuActions()
{
    int menuAction = CCUserDefault::sharedUserDefault()->getIntegerForKey("pauseAction");
    
    if (menuAction == 1) {   //展开
//        //定时创建怪物
//        this->unschedule(schedule_selector(GameLayer::initDevilOne));
//        //定时创建怪物
//        this->unschedule(schedule_selector(GameLayer::initDevilTwo));
//        //定时监测碰撞事件
//        this->unschedule(schedule_selector(GameLayer::beginCheckStrike));
//        //主角定时发射子弹
//        this->unschedule(schedule_selector(GameLayer::initHeroBullet));
//        //怪物定时发射子弹
//        this->unschedule(schedule_selector(GameLayer::initDevilBullet));
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("pauseAction", 2);
        
        //        this->menuFadIn();
        //暂停按钮动画
        CCMoveBy *moveBy = CCMoveBy::create(0.4, ccp(-250, 0));
        
        CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::menuFadIn));
        _pauseItemImage->runAction(CCSequence::create(moveBy, actionMoveDone, NULL));
    }
    else if (menuAction == 2) {   //收拢
        this->gameContinue();
//        //定时创建怪物
//        this->schedule(schedule_selector(GameLayer::initDevilOne), 1.0);
//        //定时创建怪物
//        this->schedule(schedule_selector(GameLayer::initDevilTwo), 5.0);
//        //定时监测碰撞事件
//        this->schedule(schedule_selector(GameLayer::beginCheckStrike));
//        //主角定时发射子弹
//        this->schedule(schedule_selector(GameLayer::initHeroBullet), 0.3);
//        //怪物定时发射子弹
//        this->schedule(schedule_selector(GameLayer::initDevilBullet), 1.0);
        
        this->menuFadOut();
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("pauseAction", 1);
        
        CCMoveBy *moveBy = CCMoveBy::create(0.5, ccp(250, 0));
        _pauseItemImage->runAction(moveBy);
    }
    
}

void GameLayer::menuFadIn()
{
    this->initMenu();
    
    CCActionInterval *fadIn = CCFadeIn::create(0.2);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::gamePause));
    _gameMenu->runAction(CCSequence::create(fadIn, actionMoveDone, NULL));
}

void GameLayer::menuFadOut()
{
    this->removeChild(_gameMenu, true);
}

void GameLayer::gamePause()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    //游戏暂停
    CCDirector::sharedDirector()->pause();
}

void GameLayer::gameContinue()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    //游戏继续
    CCDirector::sharedDirector()->resume();
}

void GameLayer::moveHP(float fHp)
{
    float pX = _spKong->getContentSize().width;
    float Xevery = pX / HEROHP;
    float pX1 = _spKong->getPosition().x - pX;
    float x = Xevery * fHp + pX1;
    _spHongXue->setPosition(ccp(x, _spKong->getPosition().y));
    
    int iHp = (int)fHp;
    CCString *str = CCString::createWithFormat("%i", iHp);
    _labxue->setString(str->getCString());
}

void GameLayer::moveBossHP(float fHp)
{
    float pX = _spKongBoss->getContentSize().width;
    float Xevery = pX / iBossXUE;
    float pX1 = _spKongBoss->getPosition().x - pX;
    float x = Xevery * fHp + pX1;
    _spHongXueBoss->setPosition(ccp(x, _spKongBoss->getPosition().y));
}

void GameLayer::initScore()
{
    _labScore = CCLabelTTF::create("", "Arial", 20);
    _labScore->setPosition(ccp(-200, -100));
    this->addChild(_labScore, 5);
}

void GameLayer::displayScore(float fScore, DevilOne *_devil)
{
    int i = (int)fScore;
    CCString *chScore = CCString::createWithFormat("+%d",i);
    _labScore->setString(chScore->getCString());
    _labScore->setPosition(_devil->getPosition());
    
    CCActionInterval *blink=CCBlink::create(1, 3);
    CCCallFuncN *actionDone = CCCallFuncN::create(this, callfuncN_selector(GameLayer::removeScore));
    CCFiniteTimeAction *seq = CCSequence::create(blink, actionDone, NULL);
    _labScore->runAction(seq);
}

void GameLayer::removeScore()
{
    _labScore->setPosition(ccp(-200, -100));
}




#pragma mark - 删除精灵事件
/*************************************************************************************
 函数：spriteMoveFinished(CCNode *sender)
 简介：删除精灵事件
 功能：
 
 
 *************************************************************************************/
void GameLayer::spriteMoveFinished(CCNode *sender)
{
    CCSprite *sp = (CCSprite *)sender;
    this->removeChild(sp, true);
    if (sp->getTag() == 1) {
        _heroBulletArray->removeObject(sp);
    }
    else if (sp->getTag() == 2) {
        _devilBulletArray->removeObject(sp);
    }
    else if (sp->getTag() == 3) {
        _devilOneArray->removeObject(sp);
    }
    else if (sp->getTag() == 4) {
        _heroOneArray->removeObject(sp);
    }
    else if (sp->getTag() == 5) {
        _bossBulletArray->removeObject(sp);
    }
    else if (sp->getTag() == 6) {
        _bossArray->removeObject(sp);
    }
    
}




#pragma mark - 界面切换
/*************************************************************************************
 函数：initTitleMessage()
 简介：界面切换
 功能：
 
 
 *************************************************************************************/
void GameLayer::selectBack()
{
    this->gameContinue();
    LoadingView *loadingView = LoadingView::create();
    DIRECTOR->replaceScene(loadingView);
}

void GameLayer::restratGame()
{
    this->gameContinue();
    CCDirector::sharedDirector()->replaceScene(GameScene::create());
}





#pragma mark - 游戏结束
/*************************************************************************************
 函数：initGameOverLayer()
 简介：游戏结束
 功能：
 
 
 *************************************************************************************/
void GameLayer::checkGameOver()
{
    //-----------------------英雄死亡或者消灭怪物切换界面------------------------------------
    if (iDevilOneNum > DEVILNUM) {
            if (_heroOneArray->count() <= 0) {
                CCLog("--------lose");
                this->checkGameLose();
                
            }
            else if (_devilOneArray->count() <= 0 && iDevilOneNum > DEVILNUM - 1 && _bossArray->count() <= 0) {
                
                this->checkGameWin();
//                this->checkGameLose();
//                CCLog("--------win");
            }
    }
    
}

void GameLayer::checkGameWin()
{
//    if (iDevilOneNum >= DEVILNUM && iBossNum > 0) {
//        CCLog("---%i---%i", _devilOneArray->count(), _bossArray->count());
//        if (_devilOneArray->count() <= 0 && _bossArray->count() <= 0) {
    this->unschedule(schedule_selector(GameLayer::beginCheckStrike));
    int iScoreNew = CCUserDefault::sharedUserDefault()->getIntegerForKey("scoreNew");
    iScoreNew = iScoreNew + _hero->getFHeroHp() * iBossScore;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("scoreNew", iScoreNew);
    
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("gameOverTemp", 1);
            this->initGameOverLayer();
//        }
//    }
}

void GameLayer::checkGameLose()
{
//    if (_devilOneArray->count() <= 0 && _bossArray->count() <= 0) {
//        this->checkGameWin();
//    }
//    else if (_heroOneArray->count() <= 0) {
    this->unschedule(schedule_selector(GameLayer::beginCheckStrike));
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("gameOverTemp", 2);
        this->initGameOverLayer();
//    }
}

void GameLayer::initGameOverLayer()
{
    CCDirector::sharedDirector()->resume();
    
    GameOverLayer *_gameOverLayer = GameOverLayer::create();
    CCDirector::sharedDirector()->replaceScene(_gameOverLayer);
}

























