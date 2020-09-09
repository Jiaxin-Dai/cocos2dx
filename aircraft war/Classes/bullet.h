#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace  std;

class Bullet : public cocos2d::Sprite
{

public:
	Bullet();
	~Bullet();
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	void onEnterTransitionDidFinish();
	void onExit();
	void update(float delta);
public:
	//³õÊ¼»¯×Óµ¯
	void initBullet(char* bullet_name);

};

#endif // __BULLET_H__
