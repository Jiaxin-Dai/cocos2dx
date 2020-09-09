#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
#include "time.h"
#include "vector"
#include "queue"

using namespace cocos2d;
using namespace std;




bool GameLayer::init() { //ʵ��SpriteFrameLayer���е�init��������ʼ������
	if (!Layer::init()) //���ø���ĳ�ʼ��
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin(); //��ȡ�ɼ�����ԭ������
	

	bG1 = Sprite::create("bggame.png");
    bG1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bG1, 0);
 
    bG2 = Sprite::create("bggame.png");
    bG2->setPosition(Point(visibleSize.width / 2, visibleSize.height + visibleSize.height / 2));
    this->addChild(bG2, 0);

	this->scheduleUpdate();


	_pause = MenuItemImage::create //������ͣ�˵���
			(
					"pause.png", //ƽʱ��ͼƬ
					"pause2.png", //ѡ��ʱ��ͼƬ
					"pause.png",
					CC_CALLBACK_1(GameLayer::menuPauseCallback, this) //���ʱִ�еĻص�����
					);
	_pause->setPosition(Point(visibleSize.width-150,visibleSize.height/2-800));
	_pause->setScale(0.3f);

	ko = Sprite::create("ko.png");
	ko->setAnchorPoint(Vec2(0.5, 0.5));
	ko->setScale(0.7f);
	ko->setPosition(
			Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2 -100));
	this->addChild(ko, 20);



	down_pop = Sprite::create("pause_pop.png"); //��ͣ�ĵ�������
	down_pop->setAnchorPoint(Vec2(0.5, 0.5));
	down_pop->setScale(0.7f);
	down_pop->setPosition(
			Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2 -100));
	this->addChild(down_pop, 20);

	resume_game = MenuItemImage::create(
			//�ָ���Ϸ�˵���
			"resume.png", "resume1.png", "resume.png",
			CC_CALLBACK_1(GameLayer::menuResume_GameCallback, this));
	resume_game->setAnchorPoint(Vec2(0.5, 0.5));
	resume_game->setScale(0.5f);
	resume_game->setPosition(Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2));

	caidan = MenuItemImage::create(
			//��������Ĳ˵�ѡ��
			"menu.png", "menu2.png", "menu.png",
			CC_CALLBACK_1(GameLayer::menuCaidanCallback, this));
	caidan->setAnchorPoint(Vec2(0.5, 0.5));
	caidan->setScale(0.5f);
	caidan->setPosition(Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2 - 500));

	restart = MenuItemImage::create(
			//���¿�ʼ�Ĳ˵���
			"restart.png", "restart2.png","restart.png",
			CC_CALLBACK_1(GameLayer::menuAgainCallback,this));
	restart->setAnchorPoint(Vec2(0.5, 0.5));
	restart->setScale(0.8f);
	restart->setPosition(Vec2(visibleSize.width/2,
					visibleSize.height/2+850));
	
	auto menu = Menu::create(_pause, resume_game, caidan, restart, NULL); //�����˵�����
	menu->setPosition(Point::ZERO); //���ò˵�λ��
	this->addChild(menu, 20); //���˵���ӵ�������

	initAnmiRF(); //��ʼ��֡����
	
	pigSprite = Sprite::create(); 
	pigSprite->setAnchorPoint(Point(0, 0)); 
	pigSprite->setPosition(Point(origin.x + 90, visibleSize.height/5)); 
	pigSprite->setScale(0.8f);
	pigSprite->setRotation(-90);
	pigSprite->setFlippedY(true);
	pigSprite->setFlippedX(true);
	this->addChild(pigSprite, 2); 
	pigSprite->runAction(RepeatForever::create(anmiAc[0]->clone())); //��ʼ�������ж���

	moveDistance = 5;

	auto listenerTouch = EventListenerTouchOneByOne::create(); //���Ƽ����Ĵ���
	listenerTouch->setSwallowTouches(true);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(GameLayer::onMyTouchBegin,this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(GameLayer::onMyTouchMoved,this);
	listenerTouch->onTouchCancelled =
			CC_CALLBACK_2(GameLayer::onMyTouchCalcelled,this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GameLayer::onMyTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch,
			pigSprite);


	return true;
}


//��һ���˵��ص�����
void GameLayer::menuPauseCallback(Ref* pSender) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	pause(); //��ͣ�ص������Ͷ�����Ч

	_pause->setEnabled(false);

	down_pop->setVisible(true);
	resume_game->setVisible(true);
	caidan->setVisible(true);

	down_pop->runAction(
			MoveTo::create(0.7f,
					Vec2(visibleSize.width / 2,
					visibleSize.height / 2+100)));
	resume_game->runAction(
			MoveTo::create(0.7f,
					Vec2(visibleSize.width/2+50,visibleSize.height/2+150)));
	caidan->runAction(
			MoveTo::create(0.5f,
					Vec2(visibleSize.width/2-200,visibleSize.height/2+250)));
}

void GameLayer::menuCaidanCallback(Ref* ref) {
	sceneManager->gotoMainScene();
}

void GameLayer::menuResume_GameCallback(Ref* ref) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_pause->setEnabled(true);
	resume();

	down_pop->setVisible(false);
	down_pop->setPosition(
			Vec2(visibleSize.width / 2,
					visibleSize.height / 2));
	resume_game->setVisible(false);
	resume_game->setPosition(
			Vec2(visibleSize.width/2+50,visibleSize.height/2));
	caidan->setVisible(false);
	caidan->setPosition(
			Vec2(visibleSize.width/2-100,
					visibleSize.height/2));

}
void GameLayer::menuAgainCallback(Ref* ref) {
	_pause->setEnabled(true);
	sceneManager->gotoGameScene();
}

void GameLayer::update(float delta)
{
    int posY1 = bG1->getPositionY();    //������ͼ1��Y����
    int posY2 = bG2->getPositionY();    //������ͼ2��Y����
 
    int iSpeed = 1; //��ͼ�����ٶ�
 
    /* ���ŵ�ͼ������������ŵ�ͼ�����ڵģ�����Ҫһ��������������ֿ�϶�� */
    posY1 -= iSpeed;
    posY2 -= iSpeed;
 
    /* ͼ��С */
    Size bgSize = bG1->getContentSize();
 
    /* ����1����ͼ��ȫ�뿪��Ļʱ����2����ͼ�պ���ȫ��������Ļ�ϣ���ʱ����õ�1����ͼ������
    ��2����ͼ���� */
    if (posY1 <= -bgSize.height / 2) {
        posY1 = bgSize.height + bgSize.height / 2;
    }
    /* ͬ������2����ͼ��ȫ�뿪��Ļʱ����1����ͼ�պ���ȫ��������Ļ�ϣ���ʱ����õ�2
    ����ͼ�����ڵ�1����ͼ���� */
    if (posY2 <= -bgSize.height / 2) {
        posY2 = bgSize.height + bgSize.height / 2;
    }
 
    bG1->setPositionY(posY1);
    bG2->setPositionY(posY2);


	pigSprite->runAction(MoveBy::create(1.0f, Vec2(0, 5)));

}


//��ʼ�����־���Ķ���
void GameLayer::initAnmiRF() {
	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin(); //��ȡ�ɼ�����ԭ������

	std::string run[6] = { //���ܶ���
			"pig/11.png","pig/22.png","pig/33.png","pig/44.png","pig/55.png","pig/66.png", };
	std::string rotation[6] = { "pig/11.png","pig/22.png","pig/33.png","pig/44.png","pig/55.png","pig/66.png", };
	
	Vector<SpriteFrame*> animRun;
	Vector<SpriteFrame*> animLeftRotate;

	for (int i = 0; i < 6; i++) { //���ܶ���֡���
		SpriteFrame *f = SpriteFrame::create(run[i], Rect(0, 0, 228, 226), false,Point(1, 1), Size(0, 0)); //��ȡ�˶����е�ָ������֡
		animRun.pushBack(f); //����һ�ζ����е�����֡��ŵ�������
	}
	for (int i = 0; i < 6; i++) { //��ת����֡���
		SpriteFrame *f = SpriteFrame::create(rotation[i], Rect(0, 0, 228, 226),false, Point(1, 1), Size(0, 0));
		animLeftRotate.pushBack(f);
	}
	Animation *_run = Animation::createWithSpriteFrames(animRun, 0.5f);
	anmiAc[0] = Animate::create(_run); //�������ܶ���
	anmiAc[0]->retain(); //��ʱ���ã��������ã���ֹ���Զ��ͷ�
	
	Animation *_rotation = Animation::createWithSpriteFrames(animLeftRotate,0.05f); //������ת����
	anmiAc[2] = Animate::create(_rotation);
	anmiAc[2]->retain();
}

void GameLayer::funCallback(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize(); //��ȡ�ɼ�����ߴ�
	Point origin = Director::getInstance()->getVisibleOrigin(); //��ȡ�ɼ�����ԭ������

	auto sub = Vec2(prePos, curPos);
	if(pigSprite->getPosition().x<visibleSize.width/2)
		{if (sub.x > moveDistance) { 
		rightJump();
			} 
		}
	else if(pigSprite->getPosition().x> visibleSize.width/2)
	{	if (sub.x > moveDistance) {
			leftJump();
			}
	}
	else if(pigSprite->getPosition().y >= visibleSize.height)
			gameover();
}
bool GameLayer::onMyTouchBegin(Touch *touch, Event *event) {

	
	 auto pos = touch->getLocation();
    //��ʱ��ȡ��ǰ�ƶ����λ��
    curPos = pos;
	scheduleOnce(schedule_selector(GameLayer::funCallback), 0.3f);
	return true;
}
//������
void GameLayer::leftJump() {
	
	
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	pigSprite->setFlippedX(true);
	pigSprite->setFlippedY(true);
	leftJumpAction = Spawn::create(
			Sequence::create(
					MoveTo::create(0.1f,
							Vec2(origin.x + 90+300*3, visibleSize.height/5+50)),
					MoveTo::create(0.1f,
							Vec2(origin.x + 90 +300 * 2,
									visibleSize.height / 5 + 150)),
					MoveTo::create(0.1f,
							Vec2(origin.x + 90 + 300 * 1,
									visibleSize.height / 5 + 200)),
					MoveTo::create(0.1f,
							Vec2(origin.x + 90, visibleSize.height / 5 + 150)), NULL),
			anmiAc[2], NULL);
	pigSprite->runAction(leftJumpAction);
}
void GameLayer::rightJump() { //�������ķ���
	
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
//	pigSprite->setFlippedX(true);
	pigSprite->setFlippedY(false);
	rightJumpAction = Spawn::create(
			Sequence::create(
					MoveTo::create(0.1f,
							Vec2(origin.x + 90 ,
									visibleSize.height / 5 + 150)),
					MoveTo::create(0.1f,
							Vec2(origin.x + 90 + 300 * 1,
									visibleSize.height / 5 + 200)),
					MoveTo::create(0.1f,
							Vec2(origin.x + 90 + 300* 2,
									visibleSize.height / 5 + 150)),
					MoveTo::create(0.1f,
							Vec2(origin.x + 90 + 300 * 3,
									visibleSize.height / 2 + 50)), NULL),
			anmiAc[2], NULL);
	pigSprite->runAction(rightJumpAction);
}

void GameLayer::onMyTouchMoved(Touch *touch, Event *event) {
	  auto pos = touch->getLocation();
    
    //��ʱ��ȡ��ǰ�ƶ����λ��
		curPos = pos;
}
void GameLayer::onMyTouchCalcelled(Touch *touch, Event *event) {
}
void GameLayer::onMyTouchEnded(Touch *touch, Event *event) {
	
	auto pos = touch->getLocation();
}


void GameLayer::gameover(){
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ko->setVisible(true);
	ko->setPosition(
			Vec2(visibleSize.width / 2,
					visibleSize.height / 2));
	resume_game->setVisible(true);
	caidan->setVisible(true);
	resume_game->runAction(
			MoveTo::create(0.7f,
					Vec2(visibleSize.width/2+50,visibleSize.height/2+150)));
	caidan->runAction(
			MoveTo::create(0.5f,
					Vec2(visibleSize.width/2-200,visibleSize.height/2+250)));
}



