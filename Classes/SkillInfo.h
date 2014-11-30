//
//  SkillInfo.h
//  TestGame
//
//  Created by lh on 13-12-26.
//  www.9miao.com
//

#ifndef __TestGame__SkillInfo__
#define __TestGame__SkillInfo__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
typedef enum SkillName{
	NERROR=0,
	REGIONALSKILL,
	CUTSKILL,
	CURESKILL,
	REGIONALTREATED
}SkillName;
class SkillsInfo:public CCSprite{
public:
    SkillsInfo();
    ~SkillsInfo();
    static SkillsInfo *create(int skillId);
    void initWithSkillId(int skillId);
    int m_skillRange;//ÿһ�δ������ܺ� ����ǽ�ڴ��� �뾶 �˺�����
    void regionalSKill();

    const char *m_skillName;//��������
    int m_skillTypeId;//�������� 1����� 2�������� 3��Բ�η�Χ 4����ˮ��
    const char *m_skillScript;//�˺����㹫ʽ
    int m_skillCounts;//ÿ�������������x��ʾx�μ���֮������ȴ
    
    float m_skillTimes;// ������ȴʱ��
    int m_skillBuffid;//������buffid  0Ϊû��buff
    int m_skillCri;//�������� 50��ʾ��������50%
    double m_skillCrp;//��������
    int nextid;//������������ļ���id
    int gold;//������������Ҫ�Ľ��
    int attackeffect;//�����ͷ���Ч
    int moveeffect;// �����ƶ���Ч
    int passiveeffect;//�ܻ���Ч
    int _skillId;
private:
    
};
typedef enum {
THROW=1,//Ͷ��
EARTHBULGE,//����ͻ��
CHARGE,//���
IMPRISONMENT,//����
RANGE,//��Χ
RUSH,//�����
SUMMON,
CONTINUOUSATTACK
}ENEMYSKILLTYPE;
typedef enum
{
SRANDONE=1,
ALL,
CIRCLESRANGE,
SECTORRANGE,
RELEASECOUNTS
}RANGES;
class EnemySkillInfo:public CCLayer{
public:
    EnemySkillInfo();
    ~EnemySkillInfo();
    ENEMYSKILLTYPE skillType;
    RANGES skillRange;
    int m_skillId;
    void initWithSkillId(int skillId);
    void releaseSkill(CCPoint selfpoint);
    void callbackreleaseSkill(CCNode *obj,void * sender);
    void callbackfirebomb(CCNode *obj,void *sender);
    void callbackremovebomb();
    static EnemySkillInfo *create(int skillId);
};
#endif /* defined(__TestGame__SkillInfo__) */
