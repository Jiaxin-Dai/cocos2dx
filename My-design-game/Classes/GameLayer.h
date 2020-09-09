#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "vector"
#include "queue"
#include "time.h"


using namespace cocos2d;
using namespace std;

class GameLayer : public cocos2d::Layer
{
public:

	Sprite *bG1;
	Sprite *bG2;
	Sprite* down_pop;//��ͣ������
	Sprite* ko;

	Sprite* pigSprite;//���Ǿ���
	Animate* anmiAc[2];//���Ǿ����2������
	static const int anmiIndex=0;//��ǰ��������
	
	int manHeight;
	

	SceneManager* sceneManager;//�����Ĺ�����

	MenuItemImage *restart;//���¿�ʼ��Ϸ
	MenuItemImage* resume_game;//��ͣ������ļ�����Ϸ
	MenuItemImage* caidan;//�˲˵����ڷ���������
	MenuItemImage* _pause;//���½���ͣ��ť

	Spawn *leftJumpAction;//�����Ķ���
	Spawn *rightJumpAction;//�����Ķ���


	virtual bool init();//��ʼ���ķ���
	virtual void update(float delta);


	void initAnmiRF();//��ʼ����֡����
	bool onMyTouchBegin(Touch *touch,Event *event);//���ص��ĸ�����
	void onMyTouchMoved(Touch *touch,Event *event);
	void onMyTouchEnded(Touch *touch,Event *event);
	void onMyTouchCalcelled(Touch *touch,Event *event);
	void leftJump();//�������ķ���
	void rightJump();//�������ķ���
	void gameover();

	void menuResume_GameCallback(Ref* ref);//�ָ���ͣ״̬����Ϸ�Ļص�����
	void menuCaidanCallback(Ref* ref);//�ص�������Ļص�����
	void menuPauseCallback(Ref* pSender);//��ͣ�Ļص�����
	void menuAgainCallback(Ref* ref);//���¿�ʼ�Ļص�����


	Point prePos;   //���λ��
    Point curPos;   //��ǰ��λ��
    float moveDistance;
	void funCallback(float dt);

    CREATE_FUNC(GameLayer);
};

#endif
