#include "bullet.h"
#include "manager_base.h"
//count int EMove = 35;
Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

bool Bullet::init()
{
	if (!Sprite::init())
		return false;

	return true;
}

void Bullet::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void Bullet::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void Bullet::initBullet(char* bullet_name)
{
	//初始化子弹
	auto spr_name = String::createWithFormat("plane/%s", bullet_name);
	this->initWithFile(spr_name->getCString());
}

void Bullet::update(float delta)
{
	//子弹运动
	this->setPositionY(this->getPositionY() + 5);

	//判断子弹是否移除屏幕
	if (this->getPositionY() > Director::getInstance()->getWinSize().height)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_bullet_list(this);
	}
}

