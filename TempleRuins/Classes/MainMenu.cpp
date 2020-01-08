

#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include <ResourceManager.h>
#include <SettingScene.h>
#include "GamePlay.h"

USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}


bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("background1.png");
	background->removeFromParent();
	addChild(background);
	background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/1.1 );


	auto label = Label::createWithTTF("Temple Ruin","./fonts/Marker Felt.ttf",45);
	label->setColor(Color3B::ORANGE);
	label->removeFromParent();
	label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /1.2);
	
	label->enableShadow();
	label->enableOutline(Color4B::WHITE, 1);

	addChild(label);
	auto audio = SimpleAudioEngine::getInstance();

	audio->playBackgroundMusic("./Sounds/19.mp3", true);

	
 auto play = ResourceManager::GetInstance()->GetButtonById(0);
    play->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /1.5));
    play->setScale(0.3);

    play->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
		auto audio = SimpleAudioEngine::getInstance();
	    audio->playEffect("./Sounds/sfx_clickbutton.mp3", false, 1.0f, 1.0f, 1.0f);

            if (type == ui::Widget::TouchEventType::ENDED) {
                auto scene = GamePlay::createGame();
                Director::getInstance()->replaceScene(scene);
            }
        });
	addChild(play);



    auto setting = ResourceManager::GetInstance()->GetButtonById(1);
    setting->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height /2.3));
    setting->setScale(0.5);
    
  
    setting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
		auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("./Sounds/sfx_clickbutton.mp3", false, 1.0f, 1.0f, 1.0f);

            if (type == ui::Widget::TouchEventType::ENDED) {
                auto scene = SettingScene::create();
                Director::getInstance()->replaceScene(scene);
            }
        });
	addChild(setting);

	auto shop = ResourceManager::GetInstance()->GetButtonById(2);
	shop->setPosition(Vec2(visibleSize.width /1.7, visibleSize.height / 2.3));
	shop->setScale(0.5);

	addChild(shop);
    return true;
}

void MainMenu::update(FLOAT deltaTime)
{
}

