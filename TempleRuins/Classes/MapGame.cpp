

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
	auto background = Sprite::create("SelectMap_Bg.png");
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
	close->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		auto turn = ControlMusic::GetInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("./Sounds/sfx_clickbutton.mp3", false);
			log("2");
		}

		auto scene = MainMenu::createScene();
		Director::getInstance()->replaceScene(scene);
	});
 //auto play = ResourceManager::GetInstance()->GetButtonById(0);
	auto gameplay1 = ui::Button::create("TempleRuins.png","TempleRuins_pressed.png");
	gameplay1->setPosition(Vec2(250, visibleSize.height /3));
	gameplay1->setScale(0.15);

	gameplay1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
		auto turn = ControlMusic::GetInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("./Sounds/sfx_clickbutton.mp3", false);
			log("2");
		}
            if (type == ui::Widget::TouchEventType::ENDED) {
                auto scene = GamePlay::createGame();
                Director::getInstance()->replaceScene(scene);
            }
        });
	addChild(gameplay1);

	auto gameplay2 = ui::Button::create("TuinpleRems.png", "TuinpleRems_pressed.png");
	gameplay2->setPosition(Vec2(550, visibleSize.height / 3));
	gameplay2->setScale(0.15);

	gameplay2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{auto turn = ControlMusic::GetInstance()->isSound();
	if (turn == true)
	{
		auto audio = SimpleAudioEngine::getInstance();
		//log("asd");
		audio->playEffect("./Sounds/sfx_clickbutton.mp3", false);
		log("2");
	}

		if (type == ui::Widget::TouchEventType::ENDED) {
			auto scene = GamePlay::createGame();
			Director::getInstance()->replaceScene(scene);
		}
	});
	addChild(gameplay2);

	
    return true;
}

void MapGame::update(FLOAT deltaTime)
{
}
