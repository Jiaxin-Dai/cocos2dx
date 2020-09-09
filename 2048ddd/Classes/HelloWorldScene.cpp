#include "HelloWorldScene.h"
#include "CardSprite.h"
#include <ctime>


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
void   Delay(int   time)//time*1000为秒数 
{ 
clock_t   now   =   clock(); 

while(   clock()   -   now   <   time   ); 
} 

bool HelloWorld::init()
{
 
    if ( !Layer::init() )
    {
        return false;
    }

	score = 0;
	sc1=0;
    
	Size visibleSize = Director::getInstance()->getVisibleSize();


	//加入游戏背景
	
	
	auto layerColorBG = Sprite::create("ui/2.jpg");
	layerColorBG->setPosition(ccp(visibleSize.width / 2,visibleSize.height/2));
	this->addChild(layerColorBG);
	
	//在上方加入游戏的分数
	auto labTTFCardNumberName = LabelTTF::create("score","GiddyupStd",40);
	labTTFCardNumberName->setPosition(Point(visibleSize.width/5,visibleSize.height-300));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0","GiddyupStd",30);
	labTTFCardNumber->setPosition(Point(visibleSize.width/3+10,visibleSize.height-300));
	addChild(labTTFCardNumber);
	
	labTTFCardNumber1 = LabelTTF::create("0","GiddyupStd",30);
	labTTFCardNumber1->setPosition(Point(visibleSize.width/3+15,visibleSize.height-270));
	addChild(labTTFCardNumber1);

/*
	auto spawn = Spawn::create(
		MoveBy::create(2, ccp(10, 35)),
		ScaleBy::create(2, 2),
		FadeOut::create(2),
		NULL);
	labTTFCardNumber1->runAction(
		Sequence::create(
			spawn, //执行动画动作，
			CCCallFuncN::create(CC_CALLBACK_0(LabelTTF::removeFromParent,labTTFCardNumber1)),NULL)); //然后从游戏中删除。

			*/
//********************************
	/*
	CCActionInterval* scaleLarge = CCScaleTo::create(0.3f, 2.5f, 2.5f);  
    CCActionInterval* scaleSmall = CCScaleTo::create(0.5f, 0.5f, 0.5f);  

	//回調動作，移除效果
	CCCallFunc* callFunc=CCCallFunc::create(CC_CALLBACK_0(LabelTTF::removeFromParent, labTTFCardNumber1));

	CCActionInterval* actions=CCSequence::create(scaleLarge,scaleSmall,callFunc,NULL);
    labTTFCardNumber1->runAction(actions);
//********************************
*/


	//添加标题  **********
    auto title = LabelTTF::create("DD's 2048","GiddyupStd",60);
	title->setColor(Color3B(224,51,38));
	title->setPosition(Point(visibleSize.width/2,visibleSize.height-200));
	addChild(title);

	//加入restart按钮    ************
    restartBtn = LabelTTF::create("Restart", "GiddyupStd", 40);  
    restartBtn->setColor(Color3B(103,101,112));  
    restartBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height - 250));  
    addChild(restartBtn); 

	//加入游戏的手势识别监听事件，进行绑定
	auto touchListener =EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan =CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	touchListener->onTouchEnded =CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this );
	
	//调用生成卡片的方法
	createCardSprite(visibleSize);

	//调用生成随机数
	autoCreateCardNumber();
	autoCreateCardNumber();

	return true;
}




void HelloWorld::restart(Ref* sender)  
{  
    //转场，重新开始游戏  *********************
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, HelloWorld::createScene())); 
} 

//游戏是否还能继续运行下去
void HelloWorld::doCheckGameOver(){
	bool isGameOver = true;

	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 4; x++){
			if(cardArr[x][y]->getNumber() == 0||
				(x>0 && (cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber()))||
				(x<3 && (cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber()))||
				(y>0 && (cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber()))||
				(y<3 && (cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()))){
				isGameOver = false;
			}
		}
	}
	if (isGameOver){
		//结束游戏
		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}

}

//自动生成卡片
void HelloWorld::autoCreateCardNumber(){
	int i = CCRANDOM_0_1()*4;
	int j = CCRANDOM_0_1()*4;

	//判断是否已经存在的位置
	if(cardArr[i][j]->getNumber() > 0){
		autoCreateCardNumber();
	}else{
		cardArr[i][j]->setNumber(CCRANDOM_0_1()*10<1?4:2);
	}
}

//创建卡片
void HelloWorld::createCardSprite(cocos2d::Size size){
	//求出单元格的宽度和高度
	int lon = (size.width-28)/4;

	//4*4的单元格
	for(int j = 0; j < 4;j++){
		for(int i = 0;i < 4;i++){
			CardSprite *card = CardSprite::createCardSprite(0,lon,lon,lon*j+20,lon*i+size.height/60);

			addChild(card);

			//添加卡片到二维数组中
			cardArr[j][i] = card;
		}
	}

}

//加入手势识别的事件
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	//****************
	
	gettimeofday(&tv, NULL); //记录当前时间  
    startPt = touch->getLocation(); //保存开始触摸点  
    //判断如果触摸点在restart按钮区域内则重新开始  
    if (restartBtn->getBoundingBox().containsPoint(restartBtn->convertToNodeSpace(touch->getLocation())))  
        Director::getInstance()->replaceScene(TransitionFade::create(1.2f, HelloWorld::createScene())); 
	
	
	
//	Point touchPO = touch->getLocation();

//	firstX = touchPO.x;
//	firstY = touchPO.y;

	return true;
}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	timeval tv_end;  
    gettimeofday(&tv_end, NULL);
	//获得触摸结束点 *
	 auto endPt = touch->getLocation();   
	//获取X轴跟Y轴的移动范围
	Point touchPO = touch->getLocation();
	endX = startPt.x-touchPO.x;
	endY = startPt.y-touchPO.y;
	

	//判断 x轴跟y轴的移动距离，如果x的绝对值比y轴的绝对值大的话就是左右 否则是上下滑动
	if(abs(endX) > abs(endY)){
		//左右
		if(endX+5>0){
			//左边
			if(doLeft()){
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}else{
			//右边
			if(doRight()){
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}else if(abs(endX) == abs(endY)){
	doCheckGameOver();
	}else{
		//上下
		if(endY+5>0){
			//下边
			if(doDown()){
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}else{
			//上边
			if(doUp()){
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
}

}

//上下左右的方法
bool HelloWorld::doLeft(){

bool isdo = false;  //判断代码块是否有移动或融合
	for(int y = 0; y < 4;y++){
		for(int x = 0;x < 4;x++){

			for(int x1 = x+1; x1 < 4;x1++){
				if(cardArr[x1][y]->getNumber() > 0){
					if( cardArr[x][y]->getNumber() <= 0){
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x--;
						isdo = true;
					}else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x1][y]->setNumber(0);
						
						//设置分数
						sc1 += cardArr[x][y]->getNumber();
						labTTFCardNumber1->setString(__String::createWithFormat("+%i",sc1)->getCString());

						//Delay(500);
						score +=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
						
						
						isdo = true;
					}
					break;
				}
			}
		}
	}
    sc1 = 0;
	return isdo;
}
bool HelloWorld::doRight(){


	bool isdo = false;  //判断代码块是否有移动或融合
	for(int y = 0; y < 4;y++){
		for(int x = 3;x >= 0 ;x--){

			for(int x1 = x-1; x1 >= 0 ;x1--){
				if(cardArr[x1][y]->getNumber() > 0){
					if( cardArr[x][y]->getNumber() <= 0){
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x++;
						isdo = true;
					}else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x1][y]->setNumber(0);
						
						//设置分数
						sc1 += cardArr[x][y]->getNumber();
						labTTFCardNumber1->setString(__String::createWithFormat("+%i",sc1)->getCString());

						//Delay(500);
						score +=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
						
						isdo = true;
					}
					break;
				}
			}
		}
	}
	sc1 = 0;
	return isdo;

}
bool HelloWorld::doUp(){
	bool isdo = false;
	for(int x = 0; x < 4;x++){
		for(int y = 3;y >= 0;y--){

			for(int y1 = y-1; y1 >= 0 ;y1--){
				if(cardArr[x][y1]->getNumber() > 0){
					if( cardArr[x][y]->getNumber() <= 0){
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y++;
						isdo = true;
					}else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x][y1]->setNumber(0);
						
						//设置分数
						sc1 += cardArr[x][y]->getNumber();
						labTTFCardNumber1->setString(__String::createWithFormat("+%i",sc1)->getCString());

						//Delay(500);
						score +=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
						
						isdo = true;
					}
					break;
				}
			}
		}
	}
	 sc1 = 0;
	return isdo;
}

bool HelloWorld::doDown(){
	bool isdo = false;
	for(int x = 0; x < 4;x++){
		for(int y = 0;y < 4;y++){

			for(int y1 = y+1; y1 < 4 ;y1++){
				if(cardArr[x][y1]->getNumber() > 0){
					if( cardArr[x][y]->getNumber() <= 0){
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y--;
						isdo = true;
					}else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x][y1]->setNumber(0);
						
						//设置分数
						sc1 += cardArr[x][y]->getNumber();
						labTTFCardNumber1->setString(__String::createWithFormat("+%i",sc1)->getCString());

						//Delay(500);
						score +=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
						
						isdo = true;
					}
					break;
				}
			}
		}
	}
	 sc1 = 0;
	return isdo;
}
