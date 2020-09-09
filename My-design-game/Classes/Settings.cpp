#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "time.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace std;

bool Settings::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Vec2 origin=Director::getInstance()->getVisibleOrigin();
	Size visibleSize=Director::getInstance()->getVisibleSize();



	//创建背景

	Sprite *sprite=Sprite::create("settings1.png");
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(Vec2(origin.x,origin.y));
    this->addChild(sprite);

	auto rain = ParticleRain::create();
    rain->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png"));
    rain->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-250));
	rain->setScale(2.5f); 
    rain->setTotalParticles(1000);
	rain->setSpeed(100.0f);
    rain->setLife(100.0f);
    this->addChild(rain);


	//音乐的菜单栏设置
	music=MenuItemImage::create(
								"on.png",
								"on.png",
								CC_CALLBACK_1(Settings::menuMusicCallback,this)
								);
	music->setEnabled(true);			//
	music->setScale(1.0f);				//
	music->setAnchorPoint(Vec2(0,0));	//
	music->setPosition(Vec2(origin.x+visibleSize.width-350,origin.y+visibleSize.height/2+140));

	//音效的菜单栏设置
	sound=MenuItemImage::create(
								"on.png",
								"on.png",
								CC_CALLBACK_1(Settings::menuSoundCallback,this)
								);
	sound->setEnabled(true);
	sound->setScale(1.0f);
	sound->setAnchorPoint(Vec2(0,0));
	sound->setPosition(Vec2(origin.x+visibleSize.width-350,origin.y+visibleSize.height/2-90));

	//设置音乐的开关
	if(UserDefault::getInstance()->getBoolForKey("musicFlag"))
	{
		music->setNormalSpriteFrame(SpriteFrame::create
			("on.png",Rect(0,0,256,100)));

	}else
	{
		music->setNormalSpriteFrame(SpriteFrame::create
			("off.png",Rect(0,0,256,100)));
	}


	//设置音效的开关

	 if(UserDefault::getInstance()->getBoolForKey("soundFlag"))
	{
		  sound->setNormalSpriteFrame
			  (SpriteFrame::create("on.png",Rect(0,0,256,100)));
	}else
	{
		  sound->setNormalSpriteFrame
			  (SpriteFrame::create("off.png",Rect(0,0,256,100)));
	}


	//返回菜单项的设置
	back=MenuItemImage::create(
			"back.png",
			"back.png",
			CC_CALLBACK_1(Settings::menuBackCallback,this)
			);
	back->setEnabled(true);
	back->setScale(1.0f);
	back->setAnchorPoint(Vec2(0,0));
	back->setPosition(Vec2(origin.x+50,origin.y+50));


	//创建菜单
	Menu *menu=Menu::create(music,sound,back,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,10);



	return true;
}

//音乐菜单栏的回调函数
void Settings::menuMusicCallback(Ref* ref)
{
   if(UserDefault::getInstance()->getBoolForKey("musicFlag"))
   {
	   //显示off则暂停播放音乐
	   music->setNormalSpriteFrame(SpriteFrame::create("off.png",Rect(0,0,256,100)));
	   CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	   UserDefault::getInstance()->setBoolForKey("musicFlag",false);
   }else
   {
	   //显示on则继续播放音乐
	   music->setNormalSpriteFrame(SpriteFrame::create("on.png",Rect(0,0,256,100)));
	   CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	   UserDefault::getInstance()->setBoolForKey("musicFlag",true);
   }
}

//音效菜单栏的回调函数
void Settings::menuSoundCallback(Ref* ref)
{

	if(UserDefault::getInstance()->getBoolForKey("soundFlag"))
	{
		  sound->setNormalSpriteFrame(SpriteFrame::create("off.png",Rect(0,0,256,100)));
		  UserDefault::getInstance()->setBoolForKey("soundFlag",false);
	}else
	{
		  sound->setNormalSpriteFrame(SpriteFrame::create("on.png",Rect(0,0,256,100)));
		  UserDefault::getInstance()->setBoolForKey("soundFlag",true);
	}
}

//返回菜单栏的回调函数
void Settings::menuBackCallback(Ref* ref)
{
   sceneManager->gotoMainScene();
}


