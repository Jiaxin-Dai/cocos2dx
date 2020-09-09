#include "suspand_layer.h"

SuspandLayer::SuspandLayer()
{

}

SuspandLayer::~SuspandLayer()
{

}

bool SuspandLayer::init()
{

	if (!Layer::init())
		return false;
	
	auto size = Director::getInstance()->getWinSize();
	//��ȡ�������õ���ͼƬ·��
	auto bg_name = FileUtils::getInstance()->getWritablePath() + "suspand.png";
	auto spr_bg = Sprite::create(bg_name);
	spr_bg->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spr_bg);



	//��ӻظ���Ϸ�߼�menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dictionary->objectForKey("back_game")))->getCString());
	btn_label->setSystemFontSize(40);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(SuspandLayer::back_game, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(menu);


	return true;
}

void SuspandLayer::back_game(Ref * ref)
{
	//�ظ���Ϸ�߼�
	Director::getInstance()->popScene();
}