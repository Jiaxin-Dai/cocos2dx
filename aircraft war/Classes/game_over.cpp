#include "game_over.h"
#include "start_game.h"
GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

cocos2d::Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create(); 
	scene->addChild(layer);

	return scene;
}

bool GameOver::init()
{

	if (!Layer::init())
		return false;

	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");

	auto size = Director::getInstance()->getWinSize();

	//添加背景
	auto spr_bg = Sprite::create("ui/bg.png");
	spr_bg->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(spr_bg);

	//---------------------------------设置分数------------------------------------------------
	//分数设置
	auto label_score = Label::create();
	label_score->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(size.width / 2 - label_score->getContentSize().width / 2 + 5, size.height * 0.8 - label_score->getContentSize().height / 2 - 5));
	this->addChild(label_score);

	auto label_score_num = Label::create();
	label_score_num->setSystemFontSize(30);
	label_score_num->setAnchorPoint(ccp(0, 0.5));
	label_score_num->setPosition(ccp(label_score->getPositionX() + label_score->getContentSize().width / 2 + 5, label_score->getPositionY()));
	this->addChild(label_score_num);
	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((__String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(size.width / 2 - label_best_score->getContentSize().width / 2 + 5, label_score->getPositionY() - label_best_score->getContentSize().height - 5));
	this->addChild(label_best_score);

	auto label_best_score_num = Label::create();
	label_best_score_num->setSystemFontSize(30);
	label_best_score_num->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num->setPosition(ccp(label_best_score->getPositionX() + label_best_score->getContentSize().width / 2 + 5, label_best_score->getPositionY()));
	this->addChild(label_best_score_num);

	//获取最高分
	auto score_win = UserDefault::getInstance()->getIntegerForKey("beast_score");
	auto score = UserDefault::getInstance()->getIntegerForKey("score");

	//最高分
	label_best_score_num->setString(String::createWithFormat("%d", score_win)->getCString());
	label_score_num->setString(String::createWithFormat("%d", score)->getCString());
	//-----------------------------------------------end-------------------------------------------------------

	//添加返回主页menu
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dictionary->objectForKey("back_menu")))->getCString());
	btn_label->setSystemFontSize(40);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(GameOver::menu_play, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width / 2, size.height * 0.5));
	this->addChild(menu);
	return true;
}

void GameOver::menu_play(Ref * ref)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartGame::createScene()));
}