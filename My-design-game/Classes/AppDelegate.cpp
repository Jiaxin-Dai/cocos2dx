#include "AppDelegate.h"
#include "SceneManager.h"

#include "SimpleAudioEngine.h"  //����cocos��Ƶ�����ͷ�ļ�

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}
static int register_all_packages()
{
    return 0; //flag for packages manager
}

//��ʼ������
bool AppDelegate::applicationDidFinishLaunching() {
    // ��ȡ����
    auto director = Director::getInstance();
	//��ȡ������glview
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("peppa pig");
		//���û�����glview
        director->setOpenGLView(glview);
		//����Ŀ��ֱ���,��ķֱ��ʵ���Ļ���Զ����»��������׽��ж�ֱ�������Ӧ
		glview->setDesignResolutionSize(1080,1920,ResolutionPolicy::SHOW_ALL);   
    }

	 //����Ϊ��ʾFPS����Ϣ
    director->setDisplayStats(false); //�ص���Ϣ��ʾ
	//ϵͳģ��ʱ����
    director->setAnimationInterval(1.0 / 60);

	//����Ԥ����ʱ��������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/bgmusic.wav");  

	//���ñ�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgmusic.wav",true);

	UserDefault::getInstance()->setBoolForKey("soundFlag",true);

	
	//������ʼ����
	auto sceneManager=new SceneManager();
    sceneManager->createMainScene();
    director->runWithScene(sceneManager->mainScene);

  
    
    return true;
}


//����������̨ʱ���ô˷���
void AppDelegate::applicationDidEnterBackground() {
	//ֹͣ����
    Director::getInstance()->stopAnimation();
	//����������Ļ�Ҫ��������һ����ͣ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//���������ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground() {
	//��ʼ����
    Director::getInstance()->startAnimation();
	//����������Ļ�Ҫ��������һ�俪ʼ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
	// if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}



