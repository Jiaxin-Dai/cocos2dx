#ifndef __SUSPAND_LAYER_H__
#define __SUSPAND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class SuspandLayer : public cocos2d::Layer
{
public:
	SuspandLayer();
	~SuspandLayer();

public:

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SuspandLayer);

public:
	//开始菜单点击
	void back_game(Ref * ref);

};

#endif // __SUSPAND_LAYER_H__
