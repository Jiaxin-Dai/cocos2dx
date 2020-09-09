#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "cocos2d.h"

USING_NS_CC;

class PlaneSupport;
class MainGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	CREATE_FUNC(MainGame);

	void onEnterTransitionDidFinish();
	void onExit();

	void update(float delta);
public:
	//单点触摸方法
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	
public:
	//初始化玩家飞机
	void init_hero_plane(int index);
public:
	//添加敌机
	void add_enemy(float delta);

	//添加子弹
	void add_bullet(float tm);
	//碰撞检测
	void is_crash(float tm);
	//主角死亡
	void hero_death();
	void hero_player_action_end();

	//添加物资
	void add_support(float tm);
	//添加获得物资后的子弹效果
	void add_support_bullet(float tm);

public:
	void suspend(Ref * ref);
public:
	Sprite* spr_bg1_;
	Sprite* spr_bg2_;

	//玩家飞机
	Sprite* hero_player_;
public:
	PlaneSupport* plane_support_; //支援物资
	int support_index_;//支援的物资类型
	int score_; //当前分数

	Label* label_score_num_; //当前分

	Label*label_best_score_num_; // 最高分
public:
	int plane_type_; //飞机类型
};

#endif // __HELLOWORLD_SCENE_H__
