#include "main_game.h"
#include "enemy_base.h"
#include "bullet.h"
#include "manager_base.h"
#include "plane_support.h"
#include "suspand_layer.h"
#include "game_over.h"

cocos2d::Scene* MainGame::createScene()
{
	auto scene = Scene::create();

	auto layer = MainGame::create();

	scene->addChild(layer);
	return scene;
}

bool MainGame::init()
{
	plane_support_ = NULL;
	score_ = 0;
	if (!Layer::init())
		return false;

	Size size = Director::getInstance()->getWinSize();
	//背景1
	spr_bg1_ = Sprite::create("ui/bgs.png");
	spr_bg1_->setAnchorPoint(ccp(0,0));
	spr_bg1_->setPosition(ccp(0,0));
	this->addChild(spr_bg1_);
	//背景2
	spr_bg2_ = Sprite::create("ui/bgs.png");
	spr_bg2_->setAnchorPoint(ccp(0, 0));
	spr_bg2_->setPosition(ccp(0, spr_bg1_->getContentSize().height - 2));
	this->addChild(spr_bg2_);

	//初始化飞机
	//init_hero_plane(1);

	
	//--添加暂停-----------------------------------------------
	//添加menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dictionary->objectForKey("suspend")))->getCString());
	btn_label->setSystemFontSize(30);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(MainGame::suspend, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width - btn_label->getContentSize().width / 2 - 5, size.height - btn_label->getContentSize().height / 2 - 5));
	this->addChild(menu);
	//---------------end---------------------
	//---------------------------------设置分数------------------------------------------------
	//分数设置
	auto label_score = Label::create();
	label_score->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(label_score->getContentSize().width / 2 + 5, size.height - label_score->getContentSize().height / 2 - 5));
	this->addChild(label_score);

	label_score_num_ = Label::create();
	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_score_num_->setPosition(ccp(label_score->getContentSize().width + 5, label_score->getPositionY()));
	this->addChild(label_score_num_);
	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((__String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(label_best_score->getContentSize().width / 2 + 5, label_score->getPositionY() - label_best_score->getContentSize().height - 5));
	this->addChild(label_best_score);

	label_best_score_num_ = Label::create();
	label_best_score_num_->setSystemFontSize(30);
	label_best_score_num_->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num_->setPosition(ccp(label_best_score->getContentSize().width + 5, label_best_score->getPositionY()));
	this->addChild(label_best_score_num_);
	
	//最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	label_best_score_num_->setString(String::createWithFormat("%d", score_win)->getCString());
	//当前分
	label_score_num_->setString(String::createWithFormat("%d", score_)->getCString());


	//-----------------------------------------------end-------------------------------------------------------


	//-----------单点触摸的监听器------------
	EventListenerTouchOneByOne* m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	//设置吞噬触摸
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
	//-----------------end--------------------
	return true;
}

void MainGame::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	scheduleUpdate();

	//敌机
	this->schedule(SEL_SCHEDULE(&MainGame::add_enemy), 0.3f);
	//子弹
	this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.09f);
	//碰撞检测
	this->schedule(SEL_SCHEDULE(&MainGame::is_crash));

	//物资
	this->schedule(SEL_SCHEDULE(&MainGame::add_support),9.0f);

}

void MainGame::onExit()
{
	unscheduleUpdate();
	ManagerBase::getInstance()->deleteInstance();
	Layer::onExit();
}

void MainGame::update(float delta)
{
	//实现背景滚动
	float y1 = spr_bg1_->getPositionY() - 3;
	float y2 = spr_bg2_->getPositionY() - 3;

	spr_bg1_->setPositionY(y1);
	spr_bg2_->setPositionY(y2);

	//判断背景图片是否超出边界
	if (y1 < -spr_bg1_->getContentSize().height)
	{
		spr_bg1_->setPositionY(spr_bg2_->getPositionY() + spr_bg2_->getContentSize().height - 2);

	}
	else if (y2 < -spr_bg2_->getContentSize().height)
	{
		spr_bg2_->setPositionY(spr_bg1_->getPositionY() + spr_bg1_->getContentSize().height - 2);

	}
}

bool MainGame::onTouchBegan(Touch *touch, Event *unused_event)
{
	//判断点击的区域是否在飞机上
	auto point = touch->getLocation(); //
	auto rect = hero_player_->getBoundingBox();
	if (rect.containsPoint(point))
	{
		return true;
	}
	return false;
}

void MainGame::onTouchMoved(Touch *touch, Event *unused_event)
{
	//获取飞机移动的距离
	auto add_point = touch->getLocation() - touch->getPreviousLocation();
	hero_player_->setPosition(hero_player_->getPosition() + add_point);
	
	//判断飞机移动的范围，不要超出边界
	auto size = Director::getInstance()->getWinSize();
	auto hero_size = hero_player_->getContentSize();
	
	//x方向
	if (hero_player_->getPositionX() < hero_size.width / 2)
	{
		hero_player_->setPositionX(hero_size.width / 2);
	}
	else if (hero_player_->getPositionX() > size.width - hero_size.width / 2)
	{
		hero_player_->setPositionX(size.width - hero_size.width / 2);
	}
	
	//y方向
	if (hero_player_->getPositionY() < hero_size.height / 2)
	{
		hero_player_->setPositionY(hero_size.height / 2);
	}
	else if (hero_player_->getPositionY() > size.height - hero_size.height / 2)
	{
		hero_player_->setPositionY(size.height - hero_size.height / 2);
	}
	
}

void MainGame::init_hero_plane(int index)
{
	//记录选择的飞机类型
	plane_type_ = index;

	//添加帧动画
	auto animation = Animation::create();
	for (int i = 0; i < 2; ++i)
	{
		auto str_name = String::createWithFormat("plane/heros%d_%d.png", index, i + 1);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.5);
	animation->setLoops(-1);

	//创建飞机精灵
	hero_player_ = Sprite::create(String::createWithFormat("plane/heros%d_1.png", index)->getCString());
	auto size = Director::getInstance()->getWinSize();
	hero_player_->setPosition(ccp(size.width /2 ,size.height * 0.2));
	this->addChild(hero_player_);
	hero_player_->runAction(Animate::create(animation));
	
}

void MainGame::add_enemy(float delta)
{
	//添加敌机

	//根据不同概率添加不同飞机
	
	int enemy_x = CCRANDOM_0_1() * 9 + 1;

	if (enemy_x > 6 )
	{
		enemy_x = 2;
	}
	else
	{
		enemy_x = 1;
	}

	auto enemy = EenmyBase::create();
	enemy->initEnemy(enemy_x);
	this->addChild(enemy);
	//将敌机放入管理器
	ManagerBase::getInstance()->set_enemy_list(enemy);
}

void MainGame::add_bullet(float tm )
{
	auto bullet = Bullet::create();

	//bullet->initBullet("bullet1.png");
	//更改为根据不同类型 选择不同子弹
	if (plane_type_ == 2)
	{
		bullet->initBullet("bullet2.png");
	}
	else if (plane_type_ == 3)
		bullet->initBullet("bullet3.png");
	else
		bullet->initBullet("bullet1.png");

	auto point = ccp(hero_player_->getPositionX(),hero_player_->getPositionY() + hero_player_->getContentSize().height / 2 + 10);
	bullet->setPosition(point);
	this->addChild(bullet);
	//将子弹放入管理器
	ManagerBase::getInstance()->set_bullet_list(bullet);

}

void MainGame::is_crash(float tm)
{
	//碰撞检测
	auto & enemy_list = ManagerBase::getInstance()->getEnemyList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();

	//倒序遍历
	for (int  i = enemy_list.size() - 1; i >= 0 ; --i)
	{
		//敌机
		auto enemy = enemy_list.at(i);
		if (enemy->get_hp() <= 0)
		{
			continue;
		}
		auto enemy_size = enemy->boundingBox();
		//子弹遍历
		for (int i = bullet_list.size() - 1; i >= 0; --i)
		{
			auto bullet = bullet_list.at(i);
			//判断子弹和敌机是否碰撞
			if (enemy_size.containsPoint(bullet->getPosition()))
			{
				enemy->set_hp(enemy->get_hp() - 1);

				//移除子弹
				bullet->removeFromParentAndCleanup(true);
				ManagerBase::getInstance()->remove_bullet_list(bullet);

				//如果敌机血量为0播放爆炸
				if (enemy->get_hp() <= 0)
				{
					enemy->enemy_death();
					score_ += 10;
					label_score_num_->setString(String::createWithFormat("%d", score_)->getCString());
					
				}
			}
		}
	}

	/*玩家飞机和敌机的碰撞检测*/
	for (auto i = enemy_list.size() - 1; i >= 0; --i)
	{
		auto enemy = enemy_list.at(i);

		if (enemy->get_hp() <= 0)
		{
			//如果已经毁灭就不要进行碰撞检测了
			continue;
		}
		auto rect = this->hero_player_->getBoundingBox();
		auto point = enemy->getPosition();
		//判断敌机与飞机是否碰撞 如果是 执行 主角死亡
		if (rect.containsPoint(point))
		{
			//主角死亡
			hero_death();
		}
	}

	//物资与飞机碰撞
	if (plane_support_ != NULL)
	{
		//飞机大小
		auto rect = hero_player_->getBoundingBox();
		//支援物资坐标
		auto point = plane_support_->getPosition();
		//如果飞机与支援物资发生碰撞
		if (rect.containsPoint(point))
		{
			//添加支援物资的子弹
			this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.1f, 50, 0);// 50这个参数是设置这个方法调用几次
			//停止普通子弹
			this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
			//设置延迟执行添加普通子弹时间
			this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.1f, -1, 5.0f);//5.0f 这个参数是设置这个方法 延迟多久后被调用

			plane_support_->setVisible(false);

			plane_support_ = NULL;
		}
		//移除物资
		if (plane_support_ != NULL && point.y < -plane_support_->getContentSize().height / 2)
		{
			plane_support_->removeFromParent();
			plane_support_ = NULL;
		}
	}
}

void MainGame::hero_death()
{
	//存储分数变量
	UserDefault::getInstance()->setIntegerForKey("score", score_);
	
	//最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	if (score_ > score_win)
	{
		UserDefault::getInstance()->setIntegerForKey("beast_score", score_);
	}

	//玩家飞机坠毁
	hero_player_->stopAllActions();
	this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
	this->unschedule(SEL_SCHEDULE(&MainGame::is_crash));

	//创建坠毁帧动画
	auto animation = Animation::create();

	for (int i = 1; i <= 4; ++i)
	{
		auto str_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);

	hero_player_->runAction(Sequence::create(Animate::create(animation),
		CallFunc::create(CC_CALLBACK_0(MainGame::hero_player_action_end, this)), NULL));

}

void MainGame::hero_player_action_end()
{
	//停止添加飞机
	this->unschedule(SEL_SCHEDULE(&MainGame::add_enemy));
	//调用结束页面
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GameOver::createScene()));

}

void MainGame::add_support(float tm)
{
	//初始化物资
	plane_support_ = PlaneSupport::create();
	//随机出支援物资的类型
	int index = CCRANDOM_0_1() * 2 + 1;
	support_index_ = index;
	plane_support_->init_support(index);
	this->addChild(plane_support_); 
	plane_support_->setTag(index);
}

void MainGame::add_support_bullet(float tm)
{
	//吃到物资后的子弹

	auto bullet = Bullet::create();

	if (support_index_ == 2)
		bullet->initBullet("bullet_suspand2.png");
	else
		bullet->initBullet("bullet_suspand1.png");

	auto point = Point(hero_player_->getPositionX(),
		hero_player_->getPositionY() + hero_player_->getContentSize().height / 2 + 10);
	bullet->setPosition(point);

	this->addChild(bullet);

	//将子弹添加到ManagerBase中
	ManagerBase::getInstance()->set_bullet_list(bullet);
}

void MainGame::suspend(Ref * ref)
{
	
	unscheduleUpdate();
	//先把之前不用的纹理删除
	CCTextureCache::getInstance()->removeUnusedTextures();

	//截屏-------
	auto size = Director::getInstance()->getWinSize();
	auto texture = RenderTexture::create(size.width, size.height);
	texture->begin();
	//渲染
	Director::getInstance()->getRunningScene()->visit();
	texture->end();


	texture->saveToFile("suspand.png", Image::Format::PNG);
	//--------------

	//使用schedule在下一帧中调用callback函数
	//截屏时的 下一帧
	auto back = [](float dt)
	{
		//切换到暂停界面
		auto scene = Scene::create();
		auto layer = SuspandLayer::create();
		scene->addChild(layer);
		//这里用的pushScene
		Director::getInstance()->pushScene(scene);
	};
	//这里创建Layer 是因为 移植android 时不能调用主线程中界面的下一帧 
	auto layer = Layer::create();
	this->addChild(layer);
	auto schedules = layer->getScheduler();
	schedules->schedule(back, layer, 0.0f, 0, 0.0f, false, "screenshot");
}







