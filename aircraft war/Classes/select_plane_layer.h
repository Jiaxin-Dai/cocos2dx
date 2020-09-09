
#ifndef __SELECT_PLANE_LAYER__
#define __SELECT_PLANE_LAYER__

#include <iostream>
#include "cocos2d.h"  

USING_NS_CC; 


class SelectPlaneLayer: public Layer
{
private:
    
	int page_node_; //�����ɻ�
    int cur_page_node_; //��ǰҳ��
    Point touch_down_point_;//���ʱΪֹ
    Point touch_up_point_; //̧��ʱΪֹ
    Point touch_cur_point_;
   
	float size_x;//ҳ���
    float size_y;//��
    void goToCurrNode();

public:
	SelectPlaneLayer();
	~SelectPlaneLayer();
    
    virtual bool init();
    static cocos2d::Scene* createScene();
	CREATE_FUNC(SelectPlaneLayer);
    
    void menuCloseCallback(Ref* pSender);
    
	bool onTouchBegan(Touch *touch, Event  *event);
    void onTouchMoved(Touch *touch, Event  *event);
    void onTouchEnded(Touch *touch, Event  *event);
    
	void addNode(Node *level);
};
  
#endif /* __SELECT_PLANE_LAYER__ */
