//
//  Strengthen.h
//  TestGame
//
//  Created by lh on 13-9-18.
//  www.9miao.com
//

#ifndef __TestGame__Strengthen__
#define __TestGame__Strengthen__

#include <iostream>
#include "HeaderBase.h"
#include "SocketClient.h"
#include "LoadingLayer.h"
#include "SimpleAudioEngine.h"
#include "CCScrollViewX.h"

class Strengthen:public CCLayer {
public:
    static CCScene *scene();
    SocketClient *socket;
    CCScrollViewX *scrollview;
    bool scrollFlag;
    void initLoadingLayer();//add ����ҳ��
    void changeScene();//�������� �ص�������
    void EaseInAndOut();//�л�����
    LoadingLayer *loadlayer;
    CCPoint m_beginPoint;
    CCMenu *goback_menu;
    float goback_dis;
    bool gobackflag;
    int numflag;
    int oldnumflag;
    bool hasRole;
    void getStrengt();//����ǿ����������
    void initBaseProperty(float flt);//��ʼ��ǿ������
    void analyzeData(std::string data);//��������
    void setStentgt(float flt);//��������
    void sendStrengthen(CCObject *obj);//����ǿ������
    void reciveStrengthen(CCObject *obj);//����ǿ������
    void receiveNotice(CCObject *obj);
    virtual bool init();
    const char *json_strs;
    UILayer *layer;
    CCArray *strengtenInfo;
    CCPoint m_touchPoint;
    CCPoint m_touchOffset;
    int m_nCurPage;
    CSJson::Value teamInfo;
    int  m_nPageCount;
    void finishedInit(CCObject *obj);//��ʼ�����
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    ~Strengthen();
    CREATE_FUNC(Strengthen);
private:
    CCSize size;
};
class StengthenList:public CCObject{
public:
    int djcostMoney;//����ǿ�����ɽ٣����Ľ�Ǯ
    int hpcostMoney;//ǿ����������һ�ȼ������Ǯ 0��ʾ�ѵ����� 1��ʾ����
    int attcostMoney;//ǿ����������һ�ȼ������Ǯ   ����ͬ��
    int addHp;//���β���������������
    int addAtt;//���β���������������
    int luck;//����ֵ
    int newfighting;//ǿ����С��ս����  0��ʾ����
    int newlevellimit;//�ɽٺ�ǿ���ȼ����� 0��ʾ����
    int newcolor;//�ɽٺ��������ɫ 0��ʾ���� 1�� 2�� 3�� 4��
    void setNewProperties(int djmoney,int hpmoney1,int attmoney1,int addhp,int addatt,int luck,int newfighting,int newlevellimit,int newcolor);
    std::string name;//�������
    int level;//��ǰǿ���ȼ�
    int levellimit;//ǿ���ȼ�����
    int resource;//��Դid
    int headid;//ͷ��id
    int color;//������ɫ 1�� 2�� 3�� 4��
    int hp;//ǿ�����ӵ�����
    int hpmoney;//ǿ����������һ�������Ǯ 0��ʾ�ﵽ����
    int att;//ǿ�����ӵĹ���
    int attmoney;//ǿ����������һ�ȼ�����Ҫ�Ľ�Ǯ  0��ʾ�ﵽ����
    int status;//�ɽ������Ǯ  0��ʾ�ѵ�����
    int ppid;
    StengthenList();
    ~StengthenList();
};
#endif /* defined(__TestGame__Strengthen__) */
