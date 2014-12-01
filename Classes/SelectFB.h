//
//  SelectFB.h
//  TestGame
//
//  Created by lh on 13-11-14.
//  www.9miao.com
//

#ifndef __TestGame__SelectFB__
#define __TestGame__SelectFB__

#include <iostream>
#include "HeaderBase.h"
#include "LoadingLayer.h"
#include "SocketClient.h"

// 战斗选择	FB-fight battle
// 主线、挑战、竞技、无尽、活动
// 小队阵容
class SelectFB:public CCLayer{
public:
    virtual bool init();
    int sceneFlag;
    vector<string> battleRes;
    vector<string> resArr;
    ~SelectFB();
    void addBattleTexture();
    CCSize size;
    CCString * str;
    char *jsonData;
    std::string str_callback;		// iname项，关卡名称
    SocketClient * socket;
    LoadingLayer * loading;
    UILayer * layer;
    bool mainBtnFlag;
    float diss;
    UIButton * mainBtn;
    void sendJsonData();
    void receiveJsonData(CCObject *obj);//
    void  setData(float flt);
	// 创建怪我
    void initEnemys(int eneId,int i);
    void addLoadingLayer();
    void addUILayer();
    void aaaaa(float flt);
    void enterBattleScene(CCObject *obj);
    void UIBtnFadeIn(UIButton* btn,CCLayer * layer);
    void UIBtnFadeOut(UIButton* btn,CCLayer * layer);
    void UIBtnTouchBeganEvent(CCObject * sender);
    void UIBtnTouchMovedEvent(CCObject * sender);
    void UIBtnTouchEndedEvent(CCObject * sender);
    
    int touchNum;
    bool isMoving;
    float distance;
    virtual void  registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(CCSet* set, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* set, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* set, CCEvent* event);
    
    void layerEaseOut(CCNode *node,bool dircetion);
    void callBackLayerGoOut();
    void goOutCallBack();
    CREATE_FUNC(SelectFB);
};
#endif /* defined(__TestGame__SelectFB__) */
