//
//  GameOver.h
//  TestGame
//
//  Created by lh on 13-10-28.
//  www.9miao.com
//

#ifndef __TestGame__GameOver__
#define __TestGame__GameOver__

#include <iostream>
#include "HeaderBase.h"
#include "SocketClient.h"


class GameOver:public CCLayer{
public:
    
    virtual bool init();
    SocketClient * socket;
    UILayer *layer;
    void sendGameOverMsg();//����ս��������Ϣ
    void receiveGameOverMsg(float flt);//����ս��������Ϣ
    void showRoleExp();//��ʾս�����
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    CREATE_FUNC(GameOver);
};
#endif /* defined(__TestGame__GameOver__) */
