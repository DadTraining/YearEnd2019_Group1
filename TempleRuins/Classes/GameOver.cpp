
#include "ResourceManager.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include <MainMenu.h>

USING_NS_CC;

Scene* GameOver::createScene()
{
	return GameOver::create();
}

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
	return true;
}

