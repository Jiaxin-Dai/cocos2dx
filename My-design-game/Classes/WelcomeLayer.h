#ifndef _WelcomeLayer_H__
#define _WelcomeLayer_H__

#include "cocos2d.h"								//����cocos2dͷ�ļ�
#include "SceneManager.h"							//����SceneManagerͷ�ļ�

using namespace cocos2d;							//����cocos2d�����ռ�
using namespace std;								//����std�����ռ�

class WelcomeLayer:public cocos2d::Layer{			//WelcomeLayer�������
  public:



	SceneManager* sceneManager;						//��������ָ��
	virtual bool init();							//��ʼ������



	void StartGame(Ref* ref);						//�л�����Ϸ����
	void Shezhi(Ref* ref);							//�л������ó���
	void ExitGame(Ref* ref);						//�˳���Ϸ
	CREATE_FUNC(WelcomeLayer);						//����ĺ꣬����ָ������������Ӧ��ʼ�����ͷŹ���
};
#endif
