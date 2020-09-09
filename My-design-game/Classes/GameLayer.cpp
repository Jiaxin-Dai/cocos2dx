#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Settings.h"
#include "time.h"
#include "vector"
#include "queue"

using namespace cocos2d;
using namespace std;




bool GameLayer::init() { //实现SpriteFrameLayer类中的init方法，初始化布景
	if (!Layer::init()) //调用父类的初始化
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin(); //获取可见区域原点坐标
	

	bG1 = Sprite::create("bggame.png");
    bG1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bG1, 0);
 
    bG2 = Sprite::create("bggame.png");
    bG2->setPosition(Point(visibleSize.width / 2, visibleSize.height + visibleSize.height / 2));
    this->addChild(bG2, 0);

	this->scheduleUpdate();


	_pause = MenuItemImage::create //创建暂停菜单项
			(
					"pause.png", //平时的图片
					"pause2.png", //选中时的图片
					"pause.png",
					CC_CALLBACK_1(GameLayer::menuPauseCallback, this) //点击时执行的回调方法
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



	down_pop = Sprite::create("pause_pop.png"); //暂停的弹出界面
	down_pop->setAnchorPoint(Vec2(0.5, 0.5));
	down_pop->setScale(0.7f);
	down_pop->setPosition(
			Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2 -100));
	this->addChild(down_pop, 20);

	resume_game = MenuItemImage::create(
			//恢复游戏菜单项
			"resume.png", "resume1.png", "resume.png",
			CC_CALLBACK_1(GameLayer::menuResume_GameCallback, this));
	resume_game->setAnchorPoint(Vec2(0.5, 0.5));
	resume_game->setScale(0.5f);
	resume_game->setPosition(Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2));

	caidan = MenuItemImage::create(
			//回主界面的菜单选项
			"menu.png", "menu2.png", "menu.png",
			CC_CALLBACK_1(GameLayer::menuCaidanCallback, this));
	caidan->setAnchorPoint(Vec2(0.5, 0.5));
	caidan->setScale(0.5f);
	caidan->setPosition(Vec2(origin.x + visibleSize.width / 2,
					origin.y - visibleSize.height / 2 - 500));

	restart = MenuItemImage::create(
			//重新开始的菜单项
			"restart.png", "restart2.png","restart.png",
			CC_CALLBACK_1(GameLayer::menuAgainCallback,this));
	restart->setAnchorPoint(Vec2(0.5, 0.5));
	restart->setScale(0.8f);
	restart->setPosition(Vec2(visibleSize.width/2,
					visibleSize.height/2+850));
	
	auto menu = Menu::create(_pause, resume_game, caidan, restart, NULL); //创建菜单对象
	menu->setPosition(Point::ZERO); //设置菜单位置
	this->addChild(menu, 20); //将菜单添加到布景中

	initAnmiRF(); //初始化帧动画
	
	pigSprite = Sprite::create(); 
	pigSprite->setAnchorPoint(Point(0, 0)); 
	pigSprite->setPosition(Point(origin.x + 90, visibleSize.height/5)); 
	pigSprite->setScale(0.8f);
	pigSprite->setRotation(-90);
	pigSprite->setFlippedY(true);
	pigSprite->setFlippedX(true);
	this->addChild(pigSprite, 2); 
	pigSprite->runAction(RepeatForever::create(anmiAc[0]->clone())); //开始播放爬行动画

	moveDistance = 5;

	auto listenerTouch = EventListenerTouchOneByOne::create(); //手势监听的创建
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


//下一个菜单回调方法
void GameLayer::menuPauseCallback(Ref* pSender) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	pause(); //暂停回调方法和动作特效

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
    int posY1 = bG1->getPositionY();    //背景地图1的Y坐标
    int posY2 = bG2->getPositionY();    //背景地图2的Y坐标
 
    int iSpeed = 1; //地图滚动速度
 
    /* 两张地图向左滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙） */
    posY1 -= iSpeed;
    posY2 -= iSpeed;
 
    /* 图大小 */
    Size bgSize = bG1->getContentSize();
 
    /* 当第1个地图完全离开屏幕时，第2个地图刚好完全出现在屏幕上，这时候就让第1个地图紧贴在
    第2个地图后面 */
    if (posY1 <= -bgSize.height / 2) {
        posY1 = bgSize.height + bgSize.height / 2;
    }
    /* 同理，当第2个地图完全离开屏幕时，第1个地图刚好完全出现在屏幕上，这时候就让第2
    个地图紧贴在第1个地图后面 */
    if (posY2 <= -bgSize.height / 2) {
        posY2 = bgSize.height + bgSize.height / 2;
    }
 
    bG1->setPositionY(posY1);
    bG2->setPositionY(posY2);


	pigSprite->runAction(MoveBy::create(1.0f, Vec2(0, 5)));

}


//初始化各种精灵的动画
void GameLayer::initAnmiRF() {
	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin(); //获取可见区域原点坐标

	std::string run[6] = { //奔跑动画
			"pig/11.png","pig/22.png","pig/33.png","pig/44.png","pig/55.png","pig/66.png", };
	std::string rotation[6] = { "pig/11.png","pig/22.png","pig/33.png","pig/44.png","pig/55.png","pig/66.png", };
	
	Vector<SpriteFrame*> animRun;
	Vector<SpriteFrame*> animLeftRotate;

	for (int i = 0; i < 6; i++) { //奔跑动画帧添加
		SpriteFrame *f = SpriteFrame::create(run[i], Rect(0, 0, 228, 226), false,Point(1, 1), Size(0, 0)); //获取此动画中的指定两个帧
		animRun.pushBack(f); //将这一段动画中的两个帧存放到向量中
	}
	for (int i = 0; i < 6; i++) { //旋转动画帧添加
		SpriteFrame *f = SpriteFrame::create(rotation[i], Rect(0, 0, 228, 226),false, Point(1, 1), Size(0, 0));
		animLeftRotate.pushBack(f);
	}
	Animation *_run = Animation::createWithSpriteFrames(animRun, 0.5f);
	anmiAc[0] = Animate::create(_run); //创建奔跑对象
	anmiAc[0]->retain(); //暂时不用，保持引用，防止被自动释放
	
	Animation *_rotation = Animation::createWithSpriteFrames(animLeftRotate,0.05f); //创建旋转对象
	anmiAc[2] = Animate::create(_rotation);
	anmiAc[2]->retain();
}

void GameLayer::funCallback(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize(); //获取可见区域尺寸
	Point origin = Director::getInstance()->getVisibleOrigin(); //获取可见区域原点坐标

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
    //随时获取当前移动点的位置
    curPos = pos;
	scheduleOnce(schedule_selector(GameLayer::funCallback), 0.3f);
	return true;
}
//向左跳
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
void GameLayer::rightJump() { //向右跳的方法
	
	
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
    
    //随时获取当前移动点的位置
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



