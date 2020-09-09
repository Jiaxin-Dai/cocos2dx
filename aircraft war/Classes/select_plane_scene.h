
#ifndef __SELECT_PLANE_SCENE__
#define __SELECT_PLANE_SCENE__

#include <iostream>
#include "cocos2d.h"

class SelectPlaneScene : public cocos2d::Scene
{
public:  

    virtual bool init();  
	CREATE_FUNC(SelectPlaneScene);
    void menuCloseCallback(Ref* pSender);


	static SelectPlaneScene *getInstance();
    
private:
	static SelectPlaneScene *instance_;
}; 
#endif /* __SELECT_PLANE_SCENE__ */
