//
//  RegisterScene.h
//  TestGame
//
//  Created by lh on 14-1-16.
//  www.9miao.com
//

#ifndef __TestGame__RegisterScene__
#define __TestGame__RegisterScene__

#include <iostream>
#include "HeaderBase.h"
class RegisterScene:public CCLayer{
public:
    virtual bool init();
    ~RegisterScene();
    void judgePassWord();//�ж����������Ƿ�һ��
    CCSize m_winSize;
    CCMenu *m_pBtnMenu;
    bool btn_menuflag;
    bool btnIsRuning;
    bool noticeFlag;
    int n_btnDistance;
    CCPoint oldPos;
    CCEditBox *m_pEditBox0;
    CCEditBox *m_pEditBox1;
    CCEditBox *m_pEditBox2;
    bool edit0;
    bool edit1;
    bool edit2;
    void exitFunc();//�˳��ص�����
    void sendRegisterMsg();//����ע����Ϣ
    void reciveRegisterMsg(CCObject *obj);//����ע����Ϣ
    
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    CREATE_FUNC(RegisterScene);
};
#endif /* defined(__TestGame__RegisterScene__) */
