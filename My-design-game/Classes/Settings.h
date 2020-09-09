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
	MenuItemImage *music;				//音乐控制菜单项
	MenuItemImage *sound;				//音效控制菜单项
	MenuItemImage *back;				//返回主界面菜单项

	bool musicFlag;						//音乐控制的标志
	bool soundFlag;						//音效控制的标志
		
	//回调函数
	void menuMusicCallback(Ref* ref);	
	void menuSoundCallback(Ref* ref);
	void menuBackCallback(Ref* ref);

	SceneManager *sceneManager;			//场景管理

	CREATE_FUNC(Settings);
};

#endif

