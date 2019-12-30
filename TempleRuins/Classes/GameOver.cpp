
#include "ResourceManager.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include <MainMenu.h>

USING_NS_CC;

Scene* GameOver::createScene()
{
	return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto background = ResourceManager::GetInstance()->GetBackgroundById(0);
	background->removeFromParent();
	addChild(background);
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.1);





	// update
	scheduleUpdate();

	return true;
}



