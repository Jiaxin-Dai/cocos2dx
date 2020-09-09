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
	//��ʼ���ӵ�
	auto spr_name = String::createWithFormat("plane/%s", bullet_name);
	this->initWithFile(spr_name->getCString());
}

void Bullet::update(float delta)
{
	//�ӵ��˶�
	this->setPositionY(this->getPositionY() + 5);

	//�ж��ӵ��Ƿ��Ƴ���Ļ
	if (this->getPositionY() > Director::getInstance()->getWinSize().height)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_bullet_list(this);
	}
}

