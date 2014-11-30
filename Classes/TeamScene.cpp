//
//  TeamScene.cpp
//  KouDaiXianXia
//
//  Created by lh on 14-3-11.
//  www.9miao.com
//

#include "TeamScene.h"
#include "PersonTemplate.h"
#include "MessageManager.h"
#include "message.h"
#include "AnimatePacker.h"
#include "MainView.h"
bool TeamScene::init(){
    if (!CCLayer::init()) {
        return false;
    }
    MessageManager::shareMessageManager()->sendPersonal(GameData::shareGameData()->chaId);
    AnimatePacker::getInstance()->loadAnimations("frontPerson.xml");
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TeamScene::receivePlay), "PrepareForWar", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TeamScene::getReleaseRoleMessage), "releaseRole", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TeamScene::receiveNotice), "loadingremove", NULL);
    touchIcon=NULL;
    touchHead=NULL;
    pRoleArray=CCArray::create();
    pRoleArray->retain();
    this->setTouchEnabled(true);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TeamScene::receivePetMessage), "personMessage", NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TeamScene::receiveNoticFunc), "changePosition", NULL);
    currentCount=1;
    totalCount=0;
    dragX=0.f;
    dragY=0.f;
    touchNum=0;
    moveflag=false;
     winSize=CCDirector::sharedDirector()->getWinSize();
    loadingLayer=LoadingLayer::create();
    loadingLayer->setPosition(ccp(-winSize.width, 0));
    this->addChild(loadingLayer,3);
    
   
    m_pUILayer=UILayer::create();
    this->addChild(m_pUILayer,0);
    m_pUILayer->addWidget(CCUIHELPER->createWidgetFromJsonFile("team_layer_1/team_layer_1.json"));
//    addScrollView();
    
    return true;
}
void TeamScene::receiveNotice(CCObject *obj){
    if (obj==this) {
        this->scheduleOnce(schedule_selector(TeamScene::replaceScene), 0);
    }
}
void TeamScene::replaceScene(float flt){
    CCScene *scene=MainView::scene();
    MainView *view=(MainView *)scene->getChildByTag(101);
    view->setCoin();
    view->color->removeFromParent();
    view->intensifLayer->setVisible(true);
    CCDirector::sharedDirector()->replaceScene(scene);
}
void TeamScene::reloadRole(float dt){
    HeadIcon *person=(HeadIcon *)pRoleArray->objectAtIndex(currentCount-1);
    
    person->initWithFile("fechief_stand_1_0001.png");
    person->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("fechiefa_attack")));
    person->setAnchorPoint(ccp(0, 0));
}
void TeamScene::getReleaseRoleMessage(CCObject *obj){
    Message *msg=(Message *)obj;
    CCLog("%s",msg->data);
    this->scheduleOnce(schedule_selector(TeamScene::reloadRole), 0);
}
void TeamScene::receivePetMessage(cocos2d::CCObject *sender){
    Message *msg=(Message *)sender;
    petData=msg->data;
    this->scheduleOnce(schedule_selector(TeamScene::analyzePetMessage), 0);
}
void TeamScene::analyzePetMessage(float dt){
    CSJson::Reader reader;
    CSJson::Value root;
    if (reader.parse(petData, root)) {
        CSJson::Value psinfo;
        psinfo=root["psinfo"];
        for (unsigned int i=0; i< psinfo.size(); i++) {
            int ppid=psinfo[i]["ppid"].asInt();
            HeadIcon *head=HeadIcon::create();
            head->petId=ppid;
            head->shangzhen=psinfo[i]["shangzhen"].asBool();
            head->name=psinfo[i]["name"].asString();
            head->m_nDef=psinfo[i]["deff"].asInt();
            head->m_nLevel=psinfo[i]["level"].asInt();
            head->m_nHp=psinfo[i]["hp"].asInt();
            head->m_nAtt=psinfo[i]["att"].asInt();
            head->lockFlag=psinfo[i]["flg"].asBool();
            if (head->lockFlag) {
                head->initWithFile("fechief_stand_1_0001.png");
                head->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("fechiefa_attack")));
                head->setScale(2);
            }else{
                head->initWithFile("team_layer_1/persons01_locked.png");
            }
            
            pRoleArray->addObject(head);
            for (unsigned int j=0; j< GameData::shareGameData()->roleArr->count(); j++) {
                Person *person=(Person *)GameData::shareGameData()->roleArr->objectAtIndex(j);
                if (person->lockFlag) {
                    continue;
                }
                if (ppid==person->m_id) {
                    person->lockFlag=true;
                }else{
                    person->lockFlag=false;
                }
            }
            
        }
        initHeadIcon();
    }
}
void TeamScene::receiveNoticFunc(cocos2d::CCObject *sender){
    CCString *str=(CCString *)sender;
    currentCount=str->intValue();
    this->scheduleOnce(schedule_selector(TeamScene::initProperties), 0);
}
void TeamScene::layerEaseOut(cocos2d::CCNode *node, bool dircetion){
    if (!isMoving&&dircetion) {
        node->stopActionByTag(0);
        CCMoveTo *moveto=CCMoveTo::create(0.3f, ccp(0, 0));
        isMoving=true;
        CCEaseOut *easeout=CCEaseOut::create(moveto, 1);
        CCCallFunc *func=CCCallFunc::create(this,callfunc_selector(TeamScene::goOutCallBack));//goOutCallBack
        CCSequence *seq=CCSequence::create(easeout,func,NULL);
        easeout->setTag(0);
        node->runAction(seq);
    }else if(!isMoving&&!dircetion){
        node->stopActionByTag(1);
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        CCMoveTo *moveReplace=CCMoveTo::create(0.3f, ccp(winSize.width, 0));
        isMoving=true;
        CCEaseOut *easeout=CCEaseOut::create(moveReplace, 1);
        CCCallFunc *func=CCCallFunc::create(this, callfunc_selector(TeamScene::callBackLayerGoOut));
        CCSequence *seq=CCSequence::create(easeout,func,NULL);
        seq->setTag(1);
        node->runAction(seq);
    }
}
void TeamScene::goOutCallBack(){
    isMoving=false;
}
void TeamScene::initHeadIcon(){
    for (int i=0; i<4; i++) {
        CCSprite *iconBound=CCSprite::create("icon-bound.png");
        iconBound->setTag(9000+i);
        iconBound->setPosition(ccp(125+i*220, winSize.height-iconBound->boundingBox().size.height/2+28));
        this->addChild(iconBound,2);
        
    }
    int addNum=0;
    for (unsigned int i=0; i< pRoleArray->count(); i++) {
        HeadIcon *pPer=(HeadIcon *)pRoleArray->objectAtIndex(i);
        if (pPer->shangzhen&&addNum<4) {
            CCSprite *head=(CCSprite *)this->getChildByTag(9000+addNum);
            char iconRes[20]="";
            sprintf(iconRes, "icon-%03d.png",addNum+1);
            CCSprite *headRes=CCSprite::create(iconRes);
            headRes->setTag(10000);
            headRes->setPosition(ccp(138, 132));
            head->addChild(headRes,1);
            addNum++;
        }
    }
    addScrollView();
}
CCScene *TeamScene::scene(){
    CCScene *scene=CCScene::create();
    CCLayer *layer=TeamScene::create();
    scene->addChild(layer);
    return scene;
}
void TeamScene::addScrollView(){
    CCSprite *pCoverSprite=CCSprite::create("zhegai.png");
    pCoverSprite->setAnchorPoint(ccp(0, 0));
    this->addChild(pCoverSprite,1);

    scrollview=CCScrollViewX::create(CCSizeMake((388*pRoleArray->count()+4), 488),CCSizeMake(winSize.width, 488));
    scrollview->setPosition(ccp(30, 250));
    scrollview->unscheduleAllSelectors();
    scrollview->setBounceable(true);
    this->addChild(scrollview);
    totalCount=pRoleArray->count();
    for (unsigned int i=0; i< pRoleArray->count(); i++) {
        HeadIcon *person=(HeadIcon *)pRoleArray->objectAtIndex(i);
        person->setPosition(ccp(388*1+388*(i), -370));//388*2
        scrollview->addChild(person, 1, i+100);
    }
    initProperties(0.f);
}
void TeamScene::releaseBtnEvent(CCObject *sender){
    HeadIcon *person=(HeadIcon *)pRoleArray->objectAtIndex(currentCount-1);
    MessageManager::shareMessageManager()->sendReleaseRoleMessage(person->petId);
}
void TeamScene::initProperties(float dt){
    if (currentCount>pRoleArray->count()) {
        return;
    }
    UILabel *pAttackLabel= dynamic_cast<UILabel * >(m_pUILayer->getWidgetByTag(6));
    UILabel *pHpLabel= dynamic_cast<UILabel *>(m_pUILayer->getWidgetByTag(5));
    UILabel *pDefenceLabel= dynamic_cast<UILabel *>(m_pUILayer->getWidgetByTag(7));
    UILabel *pLevelLabel=dynamic_cast<UILabel *>(m_pUILayer->getWidgetByTag(10));
    UILabel *pNameLabel= dynamic_cast<UILabel *>(m_pUILayer->getWidgetByTag(8));
    HeadIcon *person=(HeadIcon *)pRoleArray->objectAtIndex(currentCount-1);
    UIButton *releaseBtn=dynamic_cast<UIButton *>(m_pUILayer->getWidgetByTag(3));
    releaseBtn->addReleaseEvent(this, SEL_MoveEvent(&TeamScene::releaseBtnEvent));
    char attackData[10]="";
    char hpData[10]="";
    char defenceData[10]="";
    char levelData[10]="";
    char nameData[10]="";
    sprintf(attackData, "%d",person->m_nAtt);
    sprintf(hpData, "%d",person->m_nHp);
    sprintf(defenceData, "%d",person->m_nDef);
    sprintf(levelData, "%d",person->m_nLevel);
    sprintf(nameData, "%s",person->name.c_str());
    pAttackLabel->setText(attackData);
    pHpLabel->setText(hpData);
    pDefenceLabel->setText(defenceData);
    pLevelLabel->setText(levelData);
    pNameLabel->setText(nameData);
}

void  TeamScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
void TeamScene::ccTouchesBegan(CCSet* set, CCEvent* event){
    CCSetIterator  sel= set->begin();
    touchNum++;
    for (; sel!=set->end(); sel++) {
        CCTouch *pTouch=(CCTouch *)(* sel);
        if (touchIcon!=NULL) {
            return ;
        }

        if (touchNum<=1) {
            for (unsigned int i=0; i <pRoleArray->count(); i++) {
                HeadIcon *icon=(HeadIcon *)pRoleArray->objectAtIndex(i);
                if (icon->touchEvent(pTouch)&&!icon->shangzhen&&icon->lockFlag) {
                    touchIcon=icon;
                CCSprite*person=CCSprite::createWithSpriteFrameName("fechief_attack_1_0001.png");
                    person->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("fechiefa_stand")));
                    
                    person->setOpacity(GLubyte(90));
                    person->setTag(1024);
                    person->setPosition(pTouch->getLocation());
                    this->addChild(person,5);
                    dragX=pTouch->getLocation().x-touchIcon->boundingBox().origin.x;
                    dragY=pTouch->getLocation().y-touchIcon->boundingBox().origin.y;
                    oldPoint=touchIcon->getPosition();
                    
                    return ;
                }
            
            }

        }
        if (pTouch->getID()==0) {
            distance=pTouch->getLocation().x-this->boundingBox().origin.x;
            CCLog("distance   %f",distance);
        }
        
    }
}
void TeamScene::ccTouchesMoved(CCSet* set, CCEvent* event){
    CCSetIterator  sel= set->begin();

    for (; sel!=set->end(); sel++) {
        CCTouch *pTouch=(CCTouch *)(* sel);
        if (touchNum>1) {
            CCLog("ccTouchesMoved %d",pTouch->getID());
            
            if (pTouch->getID()==0) {
                CCLog("distance2   %f   %f",pTouch->getLocation().x-distance,distance);
                this->setPosition(ccp(pTouch->getLocation().x-distance, 0));
            }
        }else if (touchNum==1){
            if (touchIcon!=NULL) {
                if (moveflag&&touchIcon->lockFlag&&!touchIcon->shangzhen) {
                    CCSprite *moveIcon=(CCSprite *)this->getChildByTag(1024);
                    moveIcon->setPosition(pTouch->getLocation());
                    scrollview->setTouchEnabled(false);
                    for (int i=0; i<4; i++) {
                        CCSprite *person=(CCSprite *)this->getChildByTag(9000+i);
                        CCRect rHeadRect=CCRectMake(person->boundingBox().origin.x, person->boundingBox().origin.y, 80, 80);
                        CCRect rPersonRect=CCRectMake(moveIcon->boundingBox().origin.x, moveIcon->boundingBox().origin.y, 80, 80);
                        if (rHeadRect.intersectsRect(rPersonRect)) {
                            person->setScale(1.3f);
                            touchHead=person;
                            return;
                        }else{
                            
                            person->setScale(1);
                            touchHead=NULL;
                        }
                    }
                    return;
                }
                if (fabs(touchIcon->getPosition().x-pTouch->getLocation().x+dragX)<10&&fabs(pTouch->getLocation().y-touchIcon->getPosition().y+dragY)>10) {
                    moveflag=true;
                    CCSprite *moveIcon=(CCSprite *)this->getChildByTag(1024);
                    moveIcon->setPosition(pTouch->getLocation());
                    scrollview->setTouchEnabled(false);
                }else if(!moveflag){
                    
                    return;
                }
                
            }

        }
    }
}
void TeamScene::callBackLayerGoOut(){
    isMoving=false;
    resArr.push_back(M_LOGIN_BG);
    resArr.push_back(M_LOGIN_BTN_UP);
    resArr.push_back(M_LOGIN_BTN_DOWN);
    resArr.push_back(M_CHUANGJIAN_UP);
    resArr.push_back(M_CHUANGJIAN_DOWN);
    resArr.push_back(M_MAINVIEW_BG);
    resArr.push_back(M_MVDRAG_BG);
    resArr.push_back(M_KZBTN_UP);
    resArr.push_back(M_KZBTN_DOWN);
    resArr.push_back(M_TDBTN_UP);
    resArr.push_back(M_TDBTN_DOWN);
    resArr.push_back(M_QHBTN_UP);
    resArr.push_back(M_QHBTN_DOWN);
    resArr.push_back(M_FLBTN_UP);
    resArr.push_back(M_FLBTN_DOWN);
    loadingLayer->addImage(resArr, this);
}
void TeamScene::ccTouchesEnded(CCSet* set, CCEvent* event){
    CCSetIterator  sel= set->begin();
    touchNum--;
    for (; sel!=set->end(); sel++) {
        CCTouch *pTouch=(CCTouch *)(* sel);
        if (touchNum==0) {
            if (touchIcon!=NULL) {
                scrollview->setTouchEnabled(true);
                
                touchIcon->setPosition(oldPoint);
                
                
                if (touchHead) {
                    CCSprite *sp=(CCSprite *)this->getChildByTag(1024);
                    MessageManager::shareMessageManager()->sendPrepareForWar(touchIcon->petId, touchHead->getTag()-9000+1);
                    moveAction(sp, touchHead);
                    
                }else{
                    this->removeChildByTag(1024,true);
                    touchHead=NULL;
                    touchIcon=NULL;
                }
                
                
            }

        }else{
        
            if (this->getPosition().x>500) {
                layerEaseOut(this,false);
            }else {
                layerEaseOut(this, true);
            }
        }
    }
}
//bool TeamScene::ccTouchBegan(CCTouch* touch, CCEvent* event){
//    if (touchIcon!=NULL) {
//        return false;
//    }
//
//    for (int i=0; i<pRoleArray->count(); i++) {
//        HeadIcon *icon=(HeadIcon *)pRoleArray->objectAtIndex(i);
//        if (icon->touchEvent(touch)&&!icon->shangzhen&&icon->lockFlag) {
//            touchIcon=icon;
//            CCSprite *person=CCSprite::create("person.png");
//            person->setOpacity(GLubyte(90));
//            person->setTag(1024);
//            person->setPosition(touch->getLocation());
//            this->addChild(person,5);
//            dragX=touch->getLocation().x-touchIcon->boundingBox().origin.x;
//            dragY=touch->getLocation().y-touchIcon->boundingBox().origin.y;
//            oldPoint=touchIcon->getPosition();
//            
//            return true;
//        }
//
//    }
//    return true;
//}
//void TeamScene::ccTouchMoved(CCTouch* touch, CCEvent* event){
//    if (touchIcon!=NULL) {
//        if (moveflag&&touchIcon->lockFlag&&!touchIcon->shangzhen) {
//            CCSprite *moveIcon=(CCSprite *)this->getChildByTag(1024);
//            moveIcon->setPosition(touch->getLocation());
//            scrollview->setTouchEnabled(false);
//            for (int i=0; i<4; i++) {
//                CCSprite *person=(CCSprite *)this->getChildByTag(9000+i);
//                CCRect rHeadRect=CCRectMake(person->boundingBox().origin.x, person->boundingBox().origin.y, 80, 80);
//                CCRect rPersonRect=CCRectMake(moveIcon->boundingBox().origin.x, moveIcon->boundingBox().origin.y, 80, 80);
//                if (rHeadRect.intersectsRect(rPersonRect)) {
//                    person->setScale(1.3);
//                    touchHead=person;
//                    return;
//                }else{
//                    
//                    person->setScale(1);
//                    touchHead=NULL;
//                }
//            }
//            return;
//        }
//        if (fabs(touchIcon->getPosition().x-touch->getLocation().x+dragX)<10&&fabs(touch->getLocation().y-touchIcon->getPosition().y+dragY)>10) {
//            moveflag=true;
//            CCSprite *moveIcon=(CCSprite *)this->getChildByTag(1024);
//            moveIcon->setPosition(touch->getLocation());
//            scrollview->setTouchEnabled(false);
//        }else if(!moveflag){
//            
//            return;
//        }
//        
//    }
//
//}
//void TeamScene::ccTouchEnded(CCTouch* touch, CCEvent* event){
//    if (touchIcon!=NULL) {
//        scrollview->setTouchEnabled(true);
//        
//        touchIcon->setPosition(oldPoint);
//       
//     
//        if (touchHead) {
//            CCSprite *sp=(CCSprite *)this->getChildByTag(1024);
//            MessageManager::shareMessageManager()->sendPrepareForWar(touchIcon->petId, touchHead->getTag()-9000+1);
//            moveAction(sp, touchHead);
//            
//        }else{
//            this->removeChildByTag(1024,true);
//            touchHead=NULL;
//            touchIcon=NULL;
//        }
//        
//
//    }
//
//}
void TeamScene::moveAction(CCNode *senderNode,CCNode *aimNode){
    
    CCSprite *sp=(CCSprite *)this->getChildByTag(1024);
    setTouchEnabled(false);
    CCScaleTo *scale3=CCScaleTo::create(0.8f, 5);
    CCMoveTo *moveToAim=CCMoveTo::create(0.3f, touchHead->getPosition());
    CCScaleTo *scale1=CCScaleTo::create(0.2f, 0);
    CCDelayTime *delay=CCDelayTime::create(0.8f);
    CCCallFuncN *func=CCCallFuncN::create(this, callfuncN_selector(TeamScene::moveActionCallBack));
    
    
    CCSequence *seq1=CCSequence::create(scale3,moveToAim,func,NULL);
    CCSequence *seq2=CCSequence::create(delay,scale1,NULL);
    sp->runAction(seq1);
    sp->runAction(seq2);
}
void TeamScene::moveActionCallBack(cocos2d::CCNode *sender){
    setTouchEnabled(true);
    touchHead->removeChildByTag(10000);
    CCSprite *icon=CCSprite::create("icon-003.png");
    icon->setPosition(ccp(138, 132));
    touchHead->addChild(icon);
    touchHead->setScale(1);
    touchIcon->shangzhen=true;
    this->removeChildByTag(1024,true);
    touchHead=NULL;
    touchIcon=NULL;
}
void TeamScene::receivePlay(CCObject *sender){
    Message *msg=(Message *)sender;
    if (msg) {
        CCLog("%s",msg->data);
        JsonData=msg->data;
        this->scheduleOnce(schedule_selector(TeamScene::AnalysisJsonData), 0);
//        CSJson::Reader reader;
//        CSJson::Value root;
//        if (reader.parse(msg->data, root)) {
//           // bool result=root["result"].asBool();
//            if (root["result"].asBool()) {
//                this->scheduleOnce(schedule_selector(TeamScene::moveAction), 0);
//            }
//        }
    }
}
void TeamScene::AnalysisJsonData(float dt){
    CSJson::Reader read;
    CSJson::Value root;
    if (read.parse(JsonData.c_str(), root)) {
//        if (root["result"].asBool()) {
//            //moveAction(NULL, NULL);
//        }
    }
}
TeamScene::~TeamScene(){
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}


bool HeadIcon::init(){
    if (!CCSprite::init()) {
        return false;
    }
    icon=CCSprite::create();
    icon->setPosition(ccp(138, 132));
    this->addChild(icon);
    m_nLevel=0;
    m_nHp=0;
    m_nAtt=0;
    petId=0;
    lockFlag=false;
    return true;
}
bool HeadIcon::touchEvent(cocos2d::CCTouch *pTouch){
    CCRect touchRect=CCRectMake(pTouch->getLocation().x, pTouch->getLocation().y, 50, 50);
    CCPoint pos= this->convertToWorldSpace(CCPointZero);
    CCRect thisBound=CCRectMake(pos.x, pos.y, this->getContentSize().width, this->getContentSize().height);
    
    
    if (thisBound.intersectsRect(touchRect)) {
        CCLog("touch here");
        return true;
    }
    return false;
}
