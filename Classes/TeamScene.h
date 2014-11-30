//
//  TeamScene.h
//  KouDaiXianXia
//
//  Created by lh on 14-3-11.
//  www.9miao.com
//

#ifndef __KouDaiXianXia__TeamScene__
#define __KouDaiXianXia__TeamScene__

#include <iostream>
#include "HeaderBase.h"
#include "CCScrollViewX.h"
#include "LoadingLayer.h"
class HeadIcon:public CCSprite{
public:
    virtual bool init();
    CCSprite *icon;
    int petId;
    bool shangzhen;
    bool lockFlag;
    int m_nLevel;
    int m_nHp;
    int m_nAtt;
    std::string name;
    int m_nDef;
    bool touchEvent(CCTouch *pTouch);
    CREATE_FUNC(HeadIcon);
};
class TeamScene:public CCLayer{
public:
    virtual bool init();
    void addScrollView();
    std::vector<string> resArr;
    float dragX;
    float dragY;
    bool moveflag;
    LoadingLayer *loadingLayer;
    CCDictionary *allPet;
    HeadIcon *touchIcon;
    CCSprite *touchHead;
    CCPoint oldPoint;
    UILayer *m_pUILayer;
    int currentCount;
    int totalCount;
    CCScrollViewX *scrollview;
    CCSize winSize;
    CCArray *pRoleArray;
    int touchNum;
    void initProperties(float dt);
    string petData;
    string JsonData;
    bool isMoving;
    float distance;
    static CCScene *scene();
    void receiveNotice(CCObject *obj);
    void replaceScene(float flt);
    void analyzePetMessage(float dt);
    void receivePetMessage(CCObject *sender);
    void receiveNoticFunc(CCObject *sender);
    void initHeadIcon();
    void getReleaseRoleMessage(CCObject *obj);
    void reloadRole(float dt);
    void moveAction(CCNode *senderNode,CCNode *aimNode);
    void moveActionCallBack(CCNode *sender);
    void AnalysisJsonData(float dt);
    void receivePlay(CCObject *sender);
    void releaseBtnEvent(CCObject *sender);
    void layerEaseOut(CCNode *node,bool dircetion);
    void callBackLayerGoOut();
    void goOutCallBack();
    virtual void  registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(CCSet* set, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* set, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* set, CCEvent* event);
//    virtual void  registerWithTouchDispatcher();
//    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
//    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    ~TeamScene();
    CREATE_FUNC(TeamScene);
};

#endif /* defined(__KouDaiXianXia__TeamScene__) */
