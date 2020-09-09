#include "manager_base.h"

ManagerBase* ManagerBase::manager_ = NULL;
ManagerBase::ManagerBase()
{

}

ManagerBase::~ManagerBase()
{

}

ManagerBase* ManagerBase::getInstance()
{
	if (manager_ == NULL)
	{
		manager_ = new ManagerBase();

	}
	return manager_;
}

void ManagerBase::deleteInstance()
{
	if (manager_)
	{
		delete manager_;
		manager_ = NULL;
	}
}

void ManagerBase::set_enemy_list(EenmyBase* enemy)
{
	enemy_list_.pushBack(enemy);
}

void ManagerBase::set_bullet_list(Bullet* bullet)
{
	bullet_list_.pushBack(bullet);
}

void ManagerBase::remove_enemy_list(EenmyBase* enemy)
{
	enemy_list_.eraseObject(enemy);
}

void ManagerBase::remove_bullet_list(Bullet*bullet)
{
	bullet_list_.eraseObject(bullet);
}



