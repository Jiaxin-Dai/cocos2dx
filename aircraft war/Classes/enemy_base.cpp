#include "enemy_base.h"
#include "manager_base.h"

EenmyBase::EenmyBase()
{

}

EenmyBase::~EenmyBase()
{

}

bool EenmyBase::init()
{
	is_death_ = false;
	if (!Sprite::init())
		return false;
	return true;
}

void EenmyBase::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void EenmyBase::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

void EenmyBase::initEnemy(int name_index /* = 1 */)
{
	//敌机血量
	enemy_hp_ = name_index;
	//初始化敌机
	string name_str = String::createWithFormat("plane/enemy%d.png", name_index)->getCString();
	//添加敌机图片
	this->initWithFile(name_str);
	
	//获取屏幕大小
	Size size = Director::getInstance()->getWinSize();
	//随机敌机坐标
	Point pos = ccp(CCRANDOM_0_1()*(size.width - this->getContentSize().width) + this->getContentSize().width / 2, size.height);
	this->setPosition(pos);

}

void EenmyBase::enemy_death()
{
	is_death_ = true;
	//爆炸
	auto animation = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		auto  enemy_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(enemy_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);
	this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(), CallFunc::create(CC_CALLBACK_0(EenmyBase::remove_enemy, this)), NULL));
}

void EenmyBase::update(float delta)
{
	//如果爆炸不移动
	if (is_death_)
		return;
	//实现敌机运动
	auto point = this->getPositionY() - 5;
	this->setPositionY(point);
	//如果移动出了屏幕则从父节点中移除
	if (point < -this->getContentSize().height)
	{
		this->removeFromParentAndCleanup(true);
		remove_enemy();
	}
}

void EenmyBase::remove_enemy()
{
	ManagerBase::getInstance()->remove_enemy_list(this);
}

void EenmyBase::set_hp(int hp)
{
	enemy_hp_ = hp;
}

