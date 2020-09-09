#include "AppDelegate.h"
#include "SceneManager.h"

#include "SimpleAudioEngine.h"  //引入cocos音频引擎的头文件

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

//初始化方法
bool AppDelegate::applicationDidFinishLaunching() {
    // 获取导演
    auto director = Director::getInstance();
	//获取绘制用glview
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("peppa pig");
		//设置绘制用glview
        director->setOpenGLView(glview);
		//设置目标分辨率,别的分辨率的屏幕将自动上下或左右留白进行多分辨率自适应
		glview->setDesignResolutionSize(1080,1920,ResolutionPolicy::SHOW_ALL);   
    }

	 //设置为显示FPS等信息
    director->setDisplayStats(false); //关掉信息显示
	//系统模拟时间间隔
    director->setAnimationInterval(1.0 / 60);

	//设置预加载时背景音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/bgmusic.wav");  

	//设置背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgmusic.wav",true);

	UserDefault::getInstance()->setBoolForKey("soundFlag",true);

	
	//创建开始场景
	auto sceneManager=new SceneManager();
    sceneManager->createMainScene();
    director->runWithScene(sceneManager->mainScene);

  
    
    return true;
}


//当程序进入后台时调用此方法
void AppDelegate::applicationDidEnterBackground() {
	//停止动画
    Director::getInstance()->stopAnimation();
	//如果有声音的话要调用下面一句暂停声音播放
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//当程序进入前台时调用
void AppDelegate::applicationWillEnterForeground() {
	//开始动画
    Director::getInstance()->startAnimation();
	//如果有声音的话要调用下面一句开始声音播放
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
	// if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}



