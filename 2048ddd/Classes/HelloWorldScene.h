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

	//加入手势识别的事件
	virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event);
	//上下左右的方法
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	//自动卡片的生成
	void autoCreateCardNumber();
	//游戏是否还能继续运行下去
	void doCheckGameOver();
	void restart(Ref *sender); //重新开始游戏菜单项 **************************


private:
	//点击的元素
	int firstX,firstY,endX,endY;
	//定义一个4*4的二维数组
	CardSprite *cardArr[4][4];
	//创建卡片
	void createCardSprite(cocos2d::Size size);
	//整体游戏的分数
	int score;
	//每次加的分数
	int sc1;
	//最好分数 ***************
	int bestScore;

	//重新开始的按钮 ***************
	cocos2d::LabelTTF *restartBtn; 
	//触摸开始点******************
	cocos2d::Point startPt; 
	//当前时间***********
	timeval tv;
	//定义显示数据的控件
	cocos2d::LabelTTF *labTTFCardNumber;
	cocos2d::LabelTTF *labTTFCardNumber1;

};

#endif // __HELLOWORLD_SCENE_H__
