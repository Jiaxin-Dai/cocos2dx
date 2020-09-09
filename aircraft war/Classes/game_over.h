#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer
{
public:
	GameOver();
	~GameOver();

public:
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

public:
	//·µ»Ø²Ëµ¥µã»÷
	void menu_play(Ref * ref);

};

#endif // __GAME_OVER_H__
