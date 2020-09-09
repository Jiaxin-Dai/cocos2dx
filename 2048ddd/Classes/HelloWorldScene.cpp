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
void   Delay(int   time)//time*1000Ϊ���� 
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


	//������Ϸ����
	
	
	auto layerColorBG = Sprite::create("ui/2.jpg");
	layerColorBG->setPosition(ccp(visibleSize.width / 2,visibleSize.height/2));
	this->addChild(layerColorBG);
	
	//���Ϸ�������Ϸ�ķ���
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
			spawn, //ִ�ж���������
			CCCallFuncN::create(CC_CALLBACK_0(LabelTTF::removeFromParent,labTTFCardNumber1)),NULL)); //Ȼ�����Ϸ��ɾ����

			*/
//********************************
	/*
	CCActionInterval* scaleLarge = CCScaleTo::create(0.3f, 2.5f, 2.5f);  
    CCActionInterval* scaleSmall = CCScaleTo::create(0.5f, 0.5f, 0.5f);  

	//���{�������Ƴ�Ч��
	CCCallFunc* callFunc=CCCallFunc::create(CC_CALLBACK_0(LabelTTF::removeFromParent, labTTFCardNumber1));

	CCActionInterval* actions=CCSequence::create(scaleLarge,scaleSmall,callFunc,NULL);
    labTTFCardNumber1->runAction(actions);
//********************************
*/


	//��ӱ���  **********
    auto title = LabelTTF::create("DD's 2048","GiddyupStd",60);
	title->setColor(Color3B(224,51,38));
	title->setPosition(Point(visibleSize.width/2,visibleSize.height-200));
	addChild(title);

	//����restart��ť    ************
    restartBtn = LabelTTF::create("Restart", "GiddyupStd", 40);  
    restartBtn->setColor(Color3B(103,101,112));  
    restartBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height - 250));  
    addChild(restartBtn); 

	//������Ϸ������ʶ������¼������а�
	auto touchListener =EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan =CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	touchListener->onTouchEnded =CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this );
	
	//�������ɿ�Ƭ�ķ���
	createCardSprite(visibleSize);

	//�������������
	autoCreateCardNumber();
	autoCreateCardNumber();

	return true;
}




void HelloWorld::restart(Ref* sender)  
{  
    //ת�������¿�ʼ��Ϸ  *********************
    Director::getInstance()->replaceScene(TransitionFade::create(1.2f, HelloWorld::createScene())); 
} 

//��Ϸ�Ƿ��ܼ���������ȥ
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
		//������Ϸ
		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}

}

//�Զ����ɿ�Ƭ
void HelloWorld::autoCreateCardNumber(){
	int i = CCRANDOM_0_1()*4;
	int j = CCRANDOM_0_1()*4;

	//�ж��Ƿ��Ѿ����ڵ�λ��
	if(cardArr[i][j]->getNumber() > 0){
		autoCreateCardNumber();
	}else{
		cardArr[i][j]->setNumber(CCRANDOM_0_1()*10<1?4:2);
	}
}

//������Ƭ
void HelloWorld::createCardSprite(cocos2d::Size size){
	//�����Ԫ��Ŀ�Ⱥ͸߶�
	int lon = (size.width-28)/4;

	//4*4�ĵ�Ԫ��
	for(int j = 0; j < 4;j++){
		for(int i = 0;i < 4;i++){
			CardSprite *card = CardSprite::createCardSprite(0,lon,lon,lon*j+20,lon*i+size.height/60);

			addChild(card);

			//��ӿ�Ƭ����ά������
			cardArr[j][i] = card;
		}
	}

}

//��������ʶ����¼�
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	//****************
	
	gettimeofday(&tv, NULL); //��¼��ǰʱ��  
    startPt = touch->getLocation(); //���濪ʼ������  
    //�ж������������restart��ť�����������¿�ʼ  
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
	//��ô��������� *
	 auto endPt = touch->getLocation();   
	//��ȡX���Y����ƶ���Χ
	Point touchPO = touch->getLocation();
	endX = startPt.x-touchPO.x;
	endY = startPt.y-touchPO.y;
	

	//�ж� x���y����ƶ����룬���x�ľ���ֵ��y��ľ���ֵ��Ļ��������� ���������»���
	if(abs(endX) > abs(endY)){
		//����
		if(endX+5>0){
			//���
			if(doLeft()){
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}else{
			//�ұ�
			if(doRight()){
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}else if(abs(endX) == abs(endY)){
	doCheckGameOver();
	}else{
		//����
		if(endY+5>0){
			//�±�
			if(doDown()){
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}else{
			//�ϱ�
			if(doUp()){
				//�������������
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
}

}

//�������ҵķ���
bool HelloWorld::doLeft(){

bool isdo = false;  //�жϴ�����Ƿ����ƶ����ں�
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
						
						//���÷���
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


	bool isdo = false;  //�жϴ�����Ƿ����ƶ����ں�
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
						
						//���÷���
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
						
						//���÷���
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
						
						//���÷���
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
