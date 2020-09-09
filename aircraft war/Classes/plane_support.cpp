#include "plane_support.h"

PlaneSupport::PlaneSupport()
{

}

PlaneSupport::~PlaneSupport()
{

}

bool PlaneSupport::init()
{


	if (!Sprite::init())
		return false;

	return true;
}

void PlaneSupport::init_support(int index)
{
	//加载图片
	this->initWithFile(String::createWithFormat("plane/support%d.png", index)->getCString());

	//获取游戏屏幕大小
	auto size = Director::getInstance()->getWinSize();
	//获取自身大小
	auto content_size = this->getContentSize();
	
	//随机x,y坐标
	auto pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	auto pos_y = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	
	auto point = Point(pos_x,size.height);
	//初始化坐标
	this->setPosition(point);

	//创建贝塞尔曲线
	ccBezierConfig bezier;
	//随机x,y坐标(p1)
	pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	pos_y = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_1 = ccp(pos_x,pos_y);

	//随机x,y坐标(p2)
	pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	pos_y = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_2 = ccp(pos_x, pos_y);

	//p3坐标
	pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	bezier.endPosition = ccp(pos_x, -content_size.height);

	auto bezieraction = BezierTo::create(2.0, bezier);
	//移除自己
	auto remover_action = RemoveSelf::create();

	auto ac = Sequence::create(bezieraction, remover_action, NULL);
	this->runAction(ac);

}
