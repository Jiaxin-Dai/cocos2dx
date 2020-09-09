//
//  LevelScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "select_plane_scene.h"
#include "select_plane_layer.h"
#include "select_plane_page.h"
#include "start_game.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 

#define LAYER_NUMBER (2)

SelectPlaneScene* SelectPlaneScene::instance_;

SelectPlaneScene *SelectPlaneScene::getInstance()
{
	if (instance_ != NULL){
		return instance_;
    }
    return  NULL;
}

bool SelectPlaneScene::init()
{
    if (!Scene::init())
	{
		return false;
	}
	instance_ = this;
    
    Size size = Director::getInstance()->getWinSize();

	//��ӿɻ�������
	SelectPlaneLayer* scrollView = SelectPlaneLayer::create();

	//�ؿ�1-3
	for (int i = 1; i<= 3; ++i) {
		//��ӷɻ�����
		auto page = SelectPlanePage::create( i);
		page->setTag(i);
		scrollView->addNode(page);


    }          
	
	//---------------------����-----------------------------------------
    Sprite* spritebg =Sprite::create("ui/bg_select.png");
    spritebg->setPosition(Point(size.width / 2,size.height / 2));
    addChild(spritebg);
        
    
	this->addChild(scrollView);

      
    return true;
}  
  
void SelectPlaneScene::menuCloseCallback(Ref* pSender)
{  
}