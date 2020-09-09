#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"
#include "SceneManager.h"


using namespace cocos2d;
using namespace std;

class Settings :public cocos2d::Layer{
public:
	virtual bool init();
public:	
	MenuItemImage *music;				//���ֿ��Ʋ˵���
	MenuItemImage *sound;				//��Ч���Ʋ˵���
	MenuItemImage *back;				//����������˵���

	bool musicFlag;						//���ֿ��Ƶı�־
	bool soundFlag;						//��Ч���Ƶı�־
		
	//�ص�����
	void menuMusicCallback(Ref* ref);	
	void menuSoundCallback(Ref* ref);
	void menuBackCallback(Ref* ref);

	SceneManager *sceneManager;			//��������

	CREATE_FUNC(Settings);
};

#endif

