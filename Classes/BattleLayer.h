//
//  BattleLayer.h
//  TestGame
//
//  Created by lh on 13-11-4.
//  www.9miao.com
//

#ifndef __TestGame__BattleLayer__
#define __TestGame__BattleLayer__

#include <iostream>
#include "HeaderBase.h"
#include "SocketClient.h"
#include "GeometricRecognizer.h"
#include "PersonTemplate.h"
#include "GameOver.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Box2D.h"
#else
#include "Box2D\Box2D.h"
#endif
using namespace DollarRecognizer;
#define POINT_NUM 16
#define MIDDLE_POINT_R 255
#define MIDDLE_POINT_G 255
#define MIDDLE_POINT_B 255
#define MIDDLE_POINT_A 255
#define TOP_POINT_R	255
#define TOP_POINT_G	200
#define TOP_POINT_B	0
#define TOP_POINT_A	255
#define BOTTOM_POINT_R 255
#define BOTTOM_POINT_G 255
#define BOTTOM_POINT_B 0
#define BOTTOM_POINT_A 255
#define PTM_RATIO 60

class PinballLayer:public CCLayer{
public:
    void start();
    void stop();
    CCParticleSystemQuad *par;
    static PinballLayer *create(CCPoint enterpos);
private:
    PinballLayer();
    ~PinballLayer();
    bool initWithEnterPos(CCPoint pos);
    
    b2World *m_world;
    b2Body *m_groundbody;
    b2Fixture *m_bottomfixture;
    b2Fixture *m_ballfixture;
    void times(float dt);
};
class BattleLayer:public CCLayer{
public:
    virtual bool init();

    CCString * str;
    SocketClient * socket;
    void setRole();//���ý�ɫ��Ϣ
 
    void monsterVisible();//���￪ʼ����
protected:
	CCPoint                 m_pointPath[POINT_NUM] ;
	CCParticleSystem*       m_pParticle ;
	unsigned long			m_Index ;
	bool                    m_bTouched ;
    CCPoint                 m_touchBeganPoint ;
	CCPoint                 m_touchEndPoint ;
	long                   m_timer ;
public:
    int gestureTag;//���Ʊ��  1 ֱ��  2 ��Ȧ
    Person *selectedPerson;
    CCPoint m_personBeginPoint;
    CCPoint m_personEndedPoint;
    GeometricRecognizer * geo;
    CCScale9Sprite * touch_line;
    CCArray *touch_arr;
    CCArray *g_skillRoleArr;
    CCDictionary  *touch_dic;
    vector<int> touchNum;
    CCArray *appearArr;
    void initParticle();//��ʼ������Ч��
    Path2D path;
    GameOver *gameover;
    PinballLayer *pinballlayer;
    void enemyHited();//����������ײ
    void checkGestures(Path2D paths);//�������ͼ��
    void line();//��ʼ����
    void draw();//����draw����
    void erasureNail();//�������ߵ�β��
    void removeSkillTexture();
    void removeTouchDir(CCTouch *touch);//�Ƴ�����¼�
    void setEnemyType(EnemyRole *enemy);
    void triangle(CCPoint* vertex, CCPoint p1, CCPoint p2, GLfloat w) ;
    void skillLayerBegan(int skillId,Person *person,CCTouch *pTouch);
    void skillLayerMoved(int skillId,Person *person,CCTouch *pTouch);
    void skillLayerEnded(int skillId,Person *person,CCTouch *pTouch);
    virtual void  registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(CCSet* set, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* set, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* set, CCEvent* event);
    virtual void onEnterTransitionDidFinish();
    void onExit();
    void onEnter();
    ~BattleLayer();
    CREATE_FUNC(BattleLayer);
};

#endif /* defined(__TestGame__BattleLayer__) */
