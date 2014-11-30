//
//  PersonTemplate.h
//  TestGame
//
//  Created by lh on 13-11-26.
//  www.9miao.com
//

#ifndef __TestGame__PersonTemplate__
#define __TestGame__PersonTemplate__
#include "cocos2d.h"
#include <iostream>
#include "HeaderBase.h"
#include "SkillButton.h"
#include "SkillInfo.h"

typedef enum {
AVOID=1,
STRIKE,
PARRY,
NORMAL,
STRIKEANDPARRY
}Attackmodel;
typedef enum{
    RUN=1,
    STAND,
    ATTACK,
    ATTACKED,
    DEAD,
    TREATED
}PersonMotion;
typedef enum{
    BLOODBG=1000,
    BLOOD,
    DAOGUANG,
    ATTACKACTION,
    TOUCHMOVEACTION,
    TOUCHATTACKACTION,
    ATTACKCALLBACKFUNCACTION,
    CUREBLOODACTION
    
}PersonTag;


class Person:public CCSprite{
public:
    virtual bool init();
    CCSize size;
    int aniDir;
    bool lockFlag;
    SkillsInfo *skill;
	CCSprite *selectedCircle;
   // CCArmature* m_role;//��������
    CCSprite *m_role;
    CCLabelTTF *reduceBlood;
    bool isDead;
    //��ʼ����̬����
    void setStaticProperties(int basehp,int baseattack,float defense_coff,float dodge_coff,
                             float tenacity_coff,float parry_coff,float deflect_coff,
                             float strike_coff,float strike_result_coff,float hitrate_coff);
    //��ʼ����̬����
    void setDynamicProperties(int mAttack,int mHp,int mDefense,int mHitRate,int mDodge,
                              int mParry,int mStrike,int mStrikeResult);
    //��ù������
    float getAttackResult();
    void reduceBloodCallBack(CCNode *sender);
    virtual void loadPersonTexture();
    
    //��ɫ����
    
    bool m_skillTouch;
  virtual  void roleDead();
    void attacked();
    void attackedCallBack(CCObject *sender);
    Attackmodel attackModel();
    void animateCallBack(CCNode *sender);
    float bloodResult(Attackmodel model);
    bool  isAttacking;
    void initBones();
    void setZ();
    virtual void motionType(PersonMotion per,int dir,const char* armname);
    int hostility;//���
    //�������ԣ���̬���ԣ�
    int type;
    int res_icon;
    int res_resource;
    int m_btype;
    int m_level;//�ȼ�
    int m_id;// id
    int m_petid;//ģ��id
    std::string m_name;//����
    int skillId;
    bool isTouch;
    int m_attack;//����
    int m_hp;//Ѫ��
    int cur_hp;
    int m_defense;//����
    //��������
    int m_hittarget;//����
    int m_tenacity;//����
    int m_dodge;//����
    int m_parry;//��
    int m_strike;//����
    int m_strike_result;//��������
    //��������
    int m_range;//������Χ
    int m_speed;//�ƶ��ٶ�
    int m_attack_speed;//�����ٶ�
    //�̶�����
    int base_hp;//��׼����
    int base_attack;//��׼����
    int base_strike;//��׼����ֵ
    float defense_cf;//����ϵ��
    float dodge_cf;//����ϵ��
    float tenacity_cf;//����ϵ��
    float parry_cf;//��ϵ��
    float deflect_cf;//ƫбϵ��
    float strike_cf;//������ϵ��
    float strike_result_cf;//��������ϵ��
    float hitrate_cf;//����ϵ��
    
    float damage_rate;//�˺���
    float avoid_rate;//�����
    float parry_rate;//����
    float strike_rate;//������
    
    int m_skillTouchs;
    int m_maxTouchs;
    float DamageRate();
    float avoidRate();
    float parryRate();
    float strikeRate();
    void changeBloodCallBack();
    
    float DamageRateMultiple();
    float DamageResultMultiple();
    float HitRateMultiple();
    Person* target;
   // void getHurt();
   virtual void attackCallBack();
    void addBlood();
    void changeBlood(int changeBlood);
    void onExit();
    ~Person();
    
    CREATE_FUNC(Person);
};


class EnemyRole:public Person{
public:
    
    virtual bool init();
    ~EnemyRole();
    int oldtouchnum;
    bool ismoveing;
    virtual void enterAttackRegion(float flt);
    virtual void roleDead();
    virtual void loadPersonTexture();
    virtual void traceTarge();
    virtual void judgeSelfPos();
    virtual void runCallBack(CCNode *sender, void *num);
    void callFadeInOutFunc();
    void changeDir(float flt);
    int touchNum;
    CCSprite *select_red;
    bool isRunning;
    bool beatBackFlag;
    Person *attackMeTarget;
    CCNode *g_pNodePinBall;
    int judgePos(CCPoint m_pos,CCPoint target_pos);
    void findTarget();
    void PinballHitEnemy(CCNode *pSender);
    void PinballDis(float flt);
    bool g_bPinBallFlag;
    void MoveToTarget();
    void checkTarget();
    void onExit();
    void start();
    void setZs(float flt);
    void targetMove(CCObject *sender);
    void releaseSkillControl(float flt);
    void beatBack();
    void getHostility(float flt);
    int releaseTime;
    
    void callBackStand(CCNode * sender,void * num);
    bool isInSprite(CCTouch *touch);
    virtual void attackCallBack();
    CREATE_FUNC(EnemyRole);
};


class FriendlyRole:public Person{
    
public:
    virtual bool init();
    void start();
    CCLabelTTF *label;
    SkillButton *skillbtns;
    void moveToSelectTarget(float flt);
   // bool touchSkillBtn(CCTouch *pTouch);
    int enterNum;
    bool beatBackFlag;
    virtual void loadPersonTexture();
    void enterAttackOrgin(float flt);
    void enterAttackRegion(float flt);
    void findTarget();
    void TargetDead(CCObject *sender);
    void attackStand();
    bool isRunning;
    virtual void attackCallBack();
    void traceTarge();
    void beatBack();
    void onExit();
    void judgePos();
    void setZs(float flt);
    ~FriendlyRole();
    void touchEvent(CCTouch *touch,bool touch_flag);
    bool isInSprite(CCTouch *touch);
	void callBackStand(CCNode *sPend,void* vd);
    void callBackAttack(CCNode *sPend,void* vd);
    CREATE_FUNC(FriendlyRole);
};

class MasterRole:public Person{
public:
    virtual bool init();
    virtual void attackCallBack();
    ~MasterRole();
    attackInfo *info0;
    void start();
    void sendAttackJson();
    void receiveAttackJson(float flt);
    void touchSchedul(float flt);
    void addSkill();
    bool m_endTouchFlag;
    CCTouch *p_endTouch;
    bool m_strongTouch;
    CCTouch *touch_pos;
    bool m_touch_flag;
    SkillButton *skillbtns;
    bool m_nSkillReleaseFlag;
    int dir;
    
    bool isRunning;
    bool isMoving;
    CCParticleSystemQuad *attackPtc;
    CCParticleSystemQuad *fireBall;
    virtual void loadPersonTexture();
    void setZs(float flt);
    void enterAttackRegion(float flt);
    void judgePos();

    void enemyDead(CCObject *sender);
    void moveFireball(float flt);
   // bool touchSkillBtn(CCTouch *pTouch);
    void targetExplode();
    void whetherExplodeOver();
    void releaseSkill(CCTouch *pTouch);
    
    void touchEvent(CCTouch *touch,bool touch_flag);
    bool isInSprite(CCTouch *touch);
    void callBackStand(CCNode *node,void * sender);
    void callBackAttack(CCNode *node,void * sender);
    CREATE_FUNC(MasterRole);
};



class CureRole:public Person{
public:
    ~CureRole();
    SkillButton *skillbtns;
    virtual bool init();
    void start();
    int dir;
    Person *oldperson;
    bool isCure;
    void cureTarget();
    bool skilltouchFlag;
    void moreCureTarget(CCArray *rolearr);
    void setZs(float flt);
    void cureBlood(int changeBlood);
    void cureCallBack();
    void judgePos();
    bool isInSprite(CCTouch *touch);
    void callBackStand();
    void touchEvent(CCTouch *touch,bool touch_flag);
    virtual void loadPersonTexture();
    virtual void attackCallBack();
    CREATE_FUNC(CureRole);
};
class EnemyLongRangeBoss:public EnemyRole{
public:
    virtual bool init();
    virtual void loadPersonTexture();
    virtual void enterAttackRegion(float flt);
    virtual void traceTarge();
    virtual void judgeSelfPos();
    virtual void runCallBack();
    
    CREATE_FUNC(EnemyLongRangeBoss);
};
#endif /* defined(__TestGame__PersonTemplate__) */
