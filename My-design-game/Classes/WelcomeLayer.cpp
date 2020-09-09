#include "WelcomeLayer.h"
#include "SceneManager.h"
#include "time.h"


using namespace cocos2d;
using namespace std;

bool WelcomeLayer::init(){			//布景的初始化方法
	if(!Layer::init())				//父Layer的初始化方法
		return false;				//如果没有初始化，返回false

	Vec2 origin=Director::getInstance()->getVisibleOrigin();//获得可见区域圆点
	Size visibleSize=Director::getInstance()->getVisibleSize();//获得可见区域大小

    Sprite* sprite=Sprite::create("bg.png");//创建背景精灵
    sprite->setAnchorPoint(Vec2(0,0));			//设置锚点
	sprite->setPosition(Vec2(origin.x,origin.y));//设置位置
	auto size = sprite->getContentSize();
	sprite->setScale(visibleSize.width/size.width,visibleSize.height/size.height);
    this->addChild(sprite);						//将背景精灵添加进布景

	auto stars = ParticleSnow::create();
    stars->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png"));
    stars->setPosition(Vec2(visibleSize.width,visibleSize.height-400));
	stars->setScale(2.0f); 
    stars->setTotalParticles(500);
	stars->setSpeed(100.0f);
    stars->setLife(10.0f);
    this->addChild(stars);



	SpriteFrameCache *frameCache = SpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("1.plist");
	Vector<SpriteFrame*>spVector;
	for(int i=1;i<7;i++)
	{
		SpriteFrame *m_SpriteFrame = frameCache->spriteFrameByName(StringUtils::format("%d.png",i));
		spVector.pushBack(m_SpriteFrame);
	}
	auto m_Animation = Animation::createWithSpriteFrames(spVector);
	m_Animation->setDelayPerUnit(0.5);
	auto ani=Animate::create(m_Animation);
	auto Sp=Sprite::create();
	Sp->setTag(2);
	Sp->runAction(RepeatForever::create(ani));
	this->addChild(Sp,7);
	Sp->setPosition(Vec2(visibleSize.width/2+250,visibleSize.height/2-550));
	Sp->setScale(1.3f);

	


	MenuItemImage* menuStartButton=MenuItemImage::create(	//创建开始按钮
			"start1.png",						//默认图片
			"start2.png",						//点击后显示图片
			CC_CALLBACK_1(WelcomeLayer::StartGame,this));	//点击开始菜单回调方法
	menuStartButton->setEnabled(true);//设置显示状态为true
	menuStartButton->setScale(1.8f);	//设置缩放状态
	menuStartButton->setPosition(Vec2(origin.x+visibleSize.width/2+130,origin.y+visibleSize.height/2+100)); //设置位置




	MenuItemImage* menuShezhi=MenuItemImage::create(	//创建设置菜单
				"setting.png",			//默认图片
				"setting2.png",			//点击后显示图片
				CC_CALLBACK_1(WelcomeLayer::Shezhi,this));	//点击菜单回调方法
	menuShezhi->setEnabled(true);	//设置显示状态为true
	menuShezhi->setScale(0.8f);		//设置缩放状态
	menuShezhi->setRotation(20);
	menuShezhi->setPosition(Vec2(origin.x+visibleSize.width/2-300,origin.y+visibleSize.height/2-100));//设置位置


	MenuItemImage* menuExitGame=MenuItemImage::create( //创建退出菜单
					"quit.png",   //默认图片
					"quit.png",		//点击后显示图片
					CC_CALLBACK_1(WelcomeLayer::ExitGame,this));//点击后回调方法
	menuExitGame->setEnabled(true); //设置显示状态为true
	menuExitGame->setScale(0.4f);	//设置缩放状态
	menuExitGame->setPosition(Vec2(origin.x+visibleSize.width/2-428,origin.y+visibleSize.height/2-700));//设置位置
	
	
	Menu* menu=Menu::create(menuStartButton,menuShezhi,menuExitGame,NULL);//将菜单添加进菜单组
	menu->setPosition(Vec2::ZERO); //设置位置
	this->addChild(menu,20);	//添加进此布景


	return true;
}
void WelcomeLayer::StartGame(Ref* ref){	//去游戏界面场景方法
	sceneManager->gotoGameScene();		//调用切换到游戏场景方法
}

void WelcomeLayer::Shezhi(Ref* ref){	//去设置界面场景方法
	/*
	if(!sceneManager->settingsScene)	//如果没有创建设置场景对象
		sceneManager->createSettingsScene();//创建设置场景对象
	else
	*/
		sceneManager->gotoSettingsScene();
}




void WelcomeLayer::ExitGame(Ref* ref){//退出游戏方法
	Director::getInstance()->end();  //结束游戏
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
