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



	//��������

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


	//���ֵĲ˵�������
	music=MenuItemImage::create(
								"on.png",
								"on.png",
								CC_CALLBACK_1(Settings::menuMusicCallback,this)
								);
	music->setEnabled(true);			//
	music->setScale(1.0f);				//
	music->setAnchorPoint(Vec2(0,0));	//
	music->setPosition(Vec2(origin.x+visibleSize.width-350,origin.y+visibleSize.height/2+140));

	//��Ч�Ĳ˵�������
	sound=MenuItemImage::create(
								"on.png",
								"on.png",
								CC_CALLBACK_1(Settings::menuSoundCallback,this)
								);
	sound->setEnabled(true);
	sound->setScale(1.0f);
	sound->setAnchorPoint(Vec2(0,0));
	sound->setPosition(Vec2(origin.x+visibleSize.width-350,origin.y+visibleSize.height/2-90));

	//�������ֵĿ���
	if(UserDefault::getInstance()->getBoolForKey("musicFlag"))
	{
		music->setNormalSpriteFrame(SpriteFrame::create
			("on.png",Rect(0,0,256,100)));

	}else
	{
		music->setNormalSpriteFrame(SpriteFrame::create
			("off.png",Rect(0,0,256,100)));
	}


	//������Ч�Ŀ���

	 if(UserDefault::getInstance()->getBoolForKey("soundFlag"))
	{
		  sound->setNormalSpriteFrame
			  (SpriteFrame::create("on.png",Rect(0,0,256,100)));
	}else
	{
		  sound->setNormalSpriteFrame
			  (SpriteFrame::create("off.png",Rect(0,0,256,100)));
	}


	//���ز˵��������
	back=MenuItemImage::create(
			"back.png",
			"back.png",
			CC_CALLBACK_1(Settings::menuBackCallback,this)
			);
	back->setEnabled(true);
	back->setScale(1.0f);
	back->setAnchorPoint(Vec2(0,0));
	back->setPosition(Vec2(origin.x+50,origin.y+50));


	//�����˵�
	Menu *menu=Menu::create(music,sound,back,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,10);



	return true;
}

//���ֲ˵����Ļص�����
void Settings::menuMusicCallback(Ref* ref)
{
   if(UserDefault::getInstance()->getBoolForKey("musicFlag"))
   {
	   //��ʾoff����ͣ��������
	   music->setNormalSpriteFrame(SpriteFrame::create("off.png",Rect(0,0,256,100)));
	   CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	   UserDefault::getInstance()->setBoolForKey("musicFlag",false);
   }else
   {
	   //��ʾon�������������
	   music->setNormalSpriteFrame(SpriteFrame::create("on.png",Rect(0,0,256,100)));
	   CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	   UserDefault::getInstance()->setBoolForKey("musicFlag",true);
   }
}

//��Ч�˵����Ļص�����
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

//���ز˵����Ļص�����
void Settings::menuBackCallback(Ref* ref)
{
   sceneManager->gotoMainScene();
}


