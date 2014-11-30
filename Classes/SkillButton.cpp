//
//  SkillButton.cpp
//  TestGame
//
//  Created by lh on 13-10-22.
//  www.9miao.com
//

#include "SkillButton.h"
#include "GameData.h"
#include "AnimatePacker.h"
#include "ResourceName.h"
//static SkillButton *skill=NULL;
SkillButton::SkillButton():TouchEnable(true){

}
SkillButton::~SkillButton(){
    
}
void SkillButton::initWithDuration(float time){
    AnimatePacker::getInstance()->loadAnimations(M_HQ_TX_XML);
    CCLOG("%s",M_HQ_TX_FPNG);
    this->initWithSpriteFrameName(M_HQ_TX_FPNG);
    this->setScale(1.3f);
    this->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate(M_HQ_TX_DATA)));
    
    spirte_block=CCSprite::createWithSpriteFrameName(M_HQ_TX_FPNG);
    spirte_block->setOpacity(140);
    spirte_block->setColor(ccc3(105, 105, 105));
    CCSize size=this->getContentSize();
    spirte_block->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(spirte_block,100,10);
    spirte_block->setVisible(false);
    
    
    
    
    progress_tiem_skill = CCProgressTimer::create(spirte_block);
    progress_tiem_skill->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(progress_tiem_skill, 110, 20);
    progress_tiem_skill->setVisible(false);
    _time=time;
    
}
SkillButton *SkillButton::create(float time){
    SkillButton *skill=new SkillButton();
    if (skill) {
        
        skill->initWithDuration(time);
        //skill->autorelease();
        return skill;
    }
    CC_SAFE_DELETE(skill);
    return NULL;

}
bool SkillButton::touchSkillBtn(cocos2d::CCTouch *pTouch){
   
        CCPoint touchPoint=pTouch->getLocation();
        CCPoint reallyPoint=this->getParent()->convertToNodeSpace(touchPoint);
    CCRect rect=this->boundingBox();
    //CCRectMake(this->boundingBox().origin.x+80,this->boundingBox().origin.y+80, 100, 100);
        if(rect.containsPoint(reallyPoint)&&TouchEnable){
            SkillClickCallBack(NULL);
            return true;
        }
        return false;
}
void SkillButton::SkillClickCallBack(cocos2d::CCObject *sender){
    //�����ʼ��ȴ��ʱ����ʱ״̬�м��ܲ��ɵ��
    //��ʼ��ʱ������͸���ɰ�����Ϊ�ɼ�
    this->stopAllActions();
    this->initWithSpriteFrameName(M_HQ_TX_FPNG);
    TouchEnable=false;
    spirte_block->setVisible(true);
    //����������������˳ʱ����ת���ɼ�
    progress_tiem_skill->setType(kCCProgressTimerTypeRadial);
    progress_tiem_skill->setVisible(true);
    CCCallFuncN* action_call_back = CCCallFuncN::create(this,callfuncN_selector(SkillButton::SKillCoolDownCallBack));
    //׼��һ��5����ת360�ȵĶ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)
    action_progress_to = CCProgressTo::create(_time, 100);
    //���������鿪ʼ����һ����������(��ת���� + �ص�����(��������ȴ�����Ļص�����))
    progress_tiem_skill->runAction(CCSequence::create(action_progress_to, action_call_back, NULL));
}
void SkillButton::SKillCoolDownCallBack(cocos2d::CCNode *sender){
    TouchEnable=true;
    //�����ɰ�Ϊ���ɼ�
    spirte_block->setVisible(false);
    //��������������Ϊ���ɼ�
    progress_tiem_skill->setVisible(false);
    
    //�ü��ܰ�ť�ָ��ɵ��״̬
    this->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate(M_HQ_TX_DATA)));
}

//void SkillInfoList::setType(int skillType){
////    CCCallFunc * func;
////    CCSequence * seq;
////    CCSprite * sp;
////    CCArmature * arm;
//    switch (skillType) {
//        case 1:
//
//            break;
//        case 2:
//
//            this->cocos2d::extension::CCArmature::init("tx001");
//            
//            this->setTag(2000);
//            
//            this->getAnimation()->play("tx001");
//            this->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(SkillInfoList::removeSelf));
//            
//            break;
//        case 3:
//            break;
//        default:
//            break;
//
//    
//    }
//}
//void SkillInfoList::setSkillRegion(CCPoint centerPos){
//    CCPoint beginPos= this->getPosition();
//    
//}
//void SkillInfoList::skillHurt(float hurtPercent, int skillId,int standardAttack){
//    switch (skillId) {
//        case 0:
//            
//            break;
//            
//        default:
//            break;
//    }
//}
//
//void SkillInfoList::removeSelf(CCArmature * arm,MovementEventType type,const char * name){
//    if (type==COMPLETE) {
//        this->removeFromParent();
//        GameData::shareGameData()->SkillBtnIsTouch=false;
//    }
//}
//void SkillInfoList::screenEnemy(){
//    for (int i=0; i<GameData::shareGameData()->enemyArr->count(); i++) {
//        EnemySprite * sp= (EnemySprite *)GameData::shareGameData()->enemyArr->objectAtIndex(i);
//        float distance= ccpDistance(sp->getPosition(), this->getPosition());
//        if(distance<=300){
//            sp->changeBlood(1000);
//        }
//        
//    }
//}
