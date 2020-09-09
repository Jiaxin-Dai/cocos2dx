#include "WelcomeLayer.h"
#include "SceneManager.h"
#include "time.h"


using namespace cocos2d;
using namespace std;

bool WelcomeLayer::init(){			//�����ĳ�ʼ������
	if(!Layer::init())				//��Layer�ĳ�ʼ������
		return false;				//���û�г�ʼ��������false

	Vec2 origin=Director::getInstance()->getVisibleOrigin();//��ÿɼ�����Բ��
	Size visibleSize=Director::getInstance()->getVisibleSize();//��ÿɼ������С

    Sprite* sprite=Sprite::create("bg.png");//������������
    sprite->setAnchorPoint(Vec2(0,0));			//����ê��
	sprite->setPosition(Vec2(origin.x,origin.y));//����λ��
	auto size = sprite->getContentSize();
	sprite->setScale(visibleSize.width/size.width,visibleSize.height/size.height);
    this->addChild(sprite);						//������������ӽ�����

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

	


	MenuItemImage* menuStartButton=MenuItemImage::create(	//������ʼ��ť
			"start1.png",						//Ĭ��ͼƬ
			"start2.png",						//�������ʾͼƬ
			CC_CALLBACK_1(WelcomeLayer::StartGame,this));	//�����ʼ�˵��ص�����
	menuStartButton->setEnabled(true);//������ʾ״̬Ϊtrue
	menuStartButton->setScale(1.8f);	//��������״̬
	menuStartButton->setPosition(Vec2(origin.x+visibleSize.width/2+130,origin.y+visibleSize.height/2+100)); //����λ��




	MenuItemImage* menuShezhi=MenuItemImage::create(	//�������ò˵�
				"setting.png",			//Ĭ��ͼƬ
				"setting2.png",			//�������ʾͼƬ
				CC_CALLBACK_1(WelcomeLayer::Shezhi,this));	//����˵��ص�����
	menuShezhi->setEnabled(true);	//������ʾ״̬Ϊtrue
	menuShezhi->setScale(0.8f);		//��������״̬
	menuShezhi->setRotation(20);
	menuShezhi->setPosition(Vec2(origin.x+visibleSize.width/2-300,origin.y+visibleSize.height/2-100));//����λ��


	MenuItemImage* menuExitGame=MenuItemImage::create( //�����˳��˵�
					"quit.png",   //Ĭ��ͼƬ
					"quit.png",		//�������ʾͼƬ
					CC_CALLBACK_1(WelcomeLayer::ExitGame,this));//�����ص�����
	menuExitGame->setEnabled(true); //������ʾ״̬Ϊtrue
	menuExitGame->setScale(0.4f);	//��������״̬
	menuExitGame->setPosition(Vec2(origin.x+visibleSize.width/2-428,origin.y+visibleSize.height/2-700));//����λ��
	
	
	Menu* menu=Menu::create(menuStartButton,menuShezhi,menuExitGame,NULL);//���˵���ӽ��˵���
	menu->setPosition(Vec2::ZERO); //����λ��
	this->addChild(menu,20);	//��ӽ��˲���


	return true;
}
void WelcomeLayer::StartGame(Ref* ref){	//ȥ��Ϸ���泡������
	sceneManager->gotoGameScene();		//�����л�����Ϸ��������
}

void WelcomeLayer::Shezhi(Ref* ref){	//ȥ���ý��泡������
	/*
	if(!sceneManager->settingsScene)	//���û�д������ó�������
		sceneManager->createSettingsScene();//�������ó�������
	else
	*/
		sceneManager->gotoSettingsScene();
}




void WelcomeLayer::ExitGame(Ref* ref){//�˳���Ϸ����
	Director::getInstance()->end();  //������Ϸ
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}
