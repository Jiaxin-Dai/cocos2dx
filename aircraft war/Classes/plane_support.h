#ifndef __PLANE_SUPPORT_H__
#define __PLANE_SUPPORT_H__

#include "cocos2d.h"

USING_NS_CC;

class PlaneSupport : public cocos2d::Sprite
{

public:
	PlaneSupport();
	~PlaneSupport();
public:
	virtual bool init();


	CREATE_FUNC(PlaneSupport);

public:
	//初始化
	void init_support(int index);//根据 index不同来创建不同资源
};

#endif // __PLANE_SUPPORT_H__
