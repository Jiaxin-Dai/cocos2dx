#ifndef __SELECT_PLANE_PAGE__
#define __SELECT_PLANE_PAGE__
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class SelectPlanePage: public Node
{
public:
    //��ʼ��ѡ��ɻ�ҳ��
    bool initLevelPage(int page);
	static SelectPlanePage* create(int page);
    void menuStartCallback(Ref* pSender);

public:
	int page_;
};

#endif /* defined(__thiefTD__LevelSelectPage__) */