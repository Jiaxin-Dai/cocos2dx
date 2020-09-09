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
	Sprite* down_pop;//暂停弹出框
	Sprite* ko;

	Sprite* pigSprite;//主角精灵
	Animate* anmiAc[2];//主角精灵的2个动画
	static const int anmiIndex=0;//当前动画索引
	
	int manHeight;
	

	SceneManager* sceneManager;//场景的管理者

	MenuItemImage *restart;//重新开始游戏
	MenuItemImage* resume_game;//暂停弹出框的继续游戏
	MenuItemImage* caidan;//此菜单用于返回主界面
	MenuItemImage* _pause;//右下角暂停按钮

	Spawn *leftJumpAction;//左跳的动作
	Spawn *rightJumpAction;//右跳的动作


	virtual bool init();//初始化的方法
	virtual void update(float delta);


	void initAnmiRF();//初始化换帧精灵
	bool onMyTouchBegin(Touch *touch,Event *event);//触控的四个方法
	void onMyTouchMoved(Touch *touch,Event *event);
	void onMyTouchEnded(Touch *touch,Event *event);
	void onMyTouchCalcelled(Touch *touch,Event *event);
	void leftJump();//向左跳的方法
	void rightJump();//向右跳的方法
	void gameover();

	void menuResume_GameCallback(Ref* ref);//恢复暂停状态的游戏的回调方法
	void menuCaidanCallback(Ref* ref);//回到主界面的回调方法
	void menuPauseCallback(Ref* pSender);//暂停的回调方法
	void menuAgainCallback(Ref* ref);//重新开始的回调方法


	Point prePos;   //起点位置
    Point curPos;   //当前点位置
    float moveDistance;
	void funCallback(float dt);

    CREATE_FUNC(GameLayer);
};

#endif
