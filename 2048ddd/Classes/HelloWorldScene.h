#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	//��������ʶ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	//�������ҵķ���
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	//�Զ���Ƭ������
	void autoCreateCardNumber();
	//��Ϸ�Ƿ��ܼ���������ȥ
	void doCheckGameOver();
	void restart(Ref *sender); //���¿�ʼ��Ϸ�˵��� **************************


private:
	//�����Ԫ��
	int firstX,firstY,endX,endY;
	//����һ��4*4�Ķ�ά����
	CardSprite *cardArr[4][4];
	//������Ƭ
	void createCardSprite(cocos2d::Size size);
	//������Ϸ�ķ���
	int score;
	//ÿ�μӵķ���
	int sc1;
	//��÷��� ***************
	int bestScore;

	//���¿�ʼ�İ�ť ***************
	cocos2d::LabelTTF *restartBtn; 
	//������ʼ��******************
	cocos2d::Point startPt; 
	//��ǰʱ��***********
	timeval tv;
	//������ʾ���ݵĿؼ�
	cocos2d::LabelTTF *labTTFCardNumber;
	cocos2d::LabelTTF *labTTFCardNumber1;

};

#endif // __HELLOWORLD_SCENE_H__
