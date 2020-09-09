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
	//����ͼƬ
	this->initWithFile(String::createWithFormat("plane/support%d.png", index)->getCString());

	//��ȡ��Ϸ��Ļ��С
	auto size = Director::getInstance()->getWinSize();
	//��ȡ�����С
	auto content_size = this->getContentSize();
	
	//���x,y����
	auto pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	auto pos_y = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	
	auto point = Point(pos_x,size.height);
	//��ʼ������
	this->setPosition(point);

	//��������������
	ccBezierConfig bezier;
	//���x,y����(p1)
	pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	pos_y = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_1 = ccp(pos_x,pos_y);

	//���x,y����(p2)
	pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	pos_y = CCRANDOM_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_2 = ccp(pos_x, pos_y);

	//p3����
	pos_x = CCRANDOM_0_1()*(size.width - content_size.width) + content_size.width / 2;
	bezier.endPosition = ccp(pos_x, -content_size.height);

	auto bezieraction = BezierTo::create(2.0, bezier);
	//�Ƴ��Լ�
	auto remover_action = RemoveSelf::create();

	auto ac = Sequence::create(bezieraction, remover_action, NULL);
	this->runAction(ac);

}
