
#include "ResourceManager.h"
#include "LoadingLogo.h"
#include "SimpleAudioEngine.h"
#include <MainMenu.h>

USING_NS_CC;

Scene* LoadingLogo::createScene()
{
    return LoadingLogo::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingLogo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   
    auto loading = ResourceManager::GetInstance()->GetLoadById(0);

    loading->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

    loading->setScale(0.5);
    loading->removeFromParent();
  
    addChild(loading);
    

    

    this->schedule(schedule_selector(LoadingLogo::changeLoading), 3.0f);

    return true;
}


void LoadingLogo::changeLoading(float dt) {
    auto Scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(
        TransitionFade::create(0.5, Scene));
}

void LoadingLogo::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}