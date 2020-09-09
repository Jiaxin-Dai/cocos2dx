//
//  LevelScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "select_plane_scene.h"
#include "select_plane_layer.h"
USING_NS_CC;


#define SHORTEST_SLIDE_LENGTH (20)

SelectPlaneLayer::SelectPlaneLayer()
:page_node_(0)
, cur_page_node_(0)
{
}

SelectPlaneLayer::~SelectPlaneLayer()
{  
}
  
bool SelectPlaneLayer::init()
{  
    if (!Layer::init())
	{
		return false;
	}
	//添加触摸绑定事件
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectPlaneLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectPlaneLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectPlaneLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
	size_x = Director::getInstance()->getWinSize().width;  
	size_y = Director::getInstance()->getWinSize().height;
    
    return true;
}  
  
void SelectPlaneLayer::goToCurrNode()
{
	//滑动效果
	this->runAction(MoveTo::create(0.4f, Point(-cur_page_node_ * size_x, 0)));
}

void SelectPlaneLayer::addNode(Node *level)
{
    if (level)
    {
		level->setContentSize(Size(size_x, size_y));
		level->setPosition(Point(size_x * page_node_, 0));
        this->addChild(level);
		//记录添加几个飞机界面
		page_node_++;
    }
}

bool SelectPlaneLayer::onTouchBegan(Touch *touch, Event  *event)
{
	touch_down_point_ = touch->getLocation();
	touch_cur_point_ = touch_down_point_;
    return true;
}

void SelectPlaneLayer::onTouchMoved(Touch *touch, Event  *event)
{
    Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touch_cur_point_.x;
    Point pos_point = Point(currX, getPositionY());	

	touch_cur_point_ = touchPoint;
}

void SelectPlaneLayer::onTouchEnded(Touch *touch, Event  *event)
{
	touch_up_point_ = touch->getLocation();
	
	//坐标差
	auto dis = touch_up_point_.getDistance(touch_down_point_);

    if (dis >= SHORTEST_SLIDE_LENGTH )
    {
		if (touch_down_point_.x > touch_up_point_.x) {
			//记录当前页
			++cur_page_node_;
			if (page_node_ - 1 < cur_page_node_)
				cur_page_node_ = page_node_ - 1;
		 }
		else if (touch_down_point_.x < touch_up_point_.x) {
			//记录当前页	
			--cur_page_node_;
			if (cur_page_node_ < 0)
				cur_page_node_ = 0;
		}
		//播放滚动界面
        goToCurrNode();
    }
}
