

#include "MapGame.h"
#include "SimpleAudioEngine.h"
#include <ResourceManager.h>

#include "MapGame.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "ControlMusic.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


Scene* MapGame::createScene()
{
    return MapGame::create();
}


bool MapGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("selectmap.png");
	background->removeFromParent();
	float scale = MAX(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setScale(scale);
	//background->setScale(0.2);
	addChild(background);
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    auto close = ui::Button::create("./button/Resume.png");
	close->setPosition(Vec2(50, 370));
	close->setScale(0.8);
	addChild(close);
	close->addClickEventListener([&](Ref* event)
	{
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("./Sounds/sfx_clickbutton.mp3", false);
		}
		Director::getInstance()->replaceScene(MainMenu::create());
	});
 //auto play = ResourceManager::GetInstance()->GetButtonById(0);
	auto gameplay1 = ui::Button::create("TempleRuins.png","TempleRuins_pressed.png");
	gameplay1->setPosition(Vec2(250, visibleSize.height /2.5));
	gameplay1->setScale(0.75);

	gameplay1->addClickEventListener([&](Ref* event)
        {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("./Sounds/sfx_clickbutton.mp3", false);
		}
		Director::getInstance()->replaceScene(GamePlay::createGame());
        });
	addChild(gameplay1);

	auto gameplay2 = ui::Button::create("TuinpleRems.png", "TuinpleRems_pressed.png");
	gameplay2->setPosition(Vec2(550, visibleSize.height / 2.5));
	gameplay2->setScale(0.75);

	gameplay2->addClickEventListener([&](Ref* event)
	{if (ControlMusic::GetInstance()->isSound())
	{
		SimpleAudioEngine::getInstance()->playEffect("./Sounds/sfx_clickbutton.mp3", false);
	}
	Director::getInstance()->replaceScene(GamePlay::createGame());
	});
	addChild(gameplay2);

	
    return true;
}

void MapGame::update(FLOAT deltaTime)
{
}
