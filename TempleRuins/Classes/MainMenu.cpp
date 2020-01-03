/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
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
	auto background = ResourceManager::GetInstance()->GetBackgroundById(0);
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
    play->removeFromParent();

    addChild(play,2);
    play->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
		auto audio = SimpleAudioEngine::getInstance();
	    audio->playEffect("./Sounds/sfx_clickbutton.mp3", false, 1.0f, 1.0f, 1.0f);

            if (type == ui::Widget::TouchEventType::ENDED) {
                auto scene = GamePlay::createGame();
                Director::getInstance()->replaceScene(scene);
            }
        });


    auto setting = ResourceManager::GetInstance()->GetButtonById(1);

   
    setting->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height /2.3));

    setting->setScale(0.5);
    setting->removeFromParent();
	
    addChild(setting,2);
    setting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        { auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("./Sounds/sfx_clickbutton.mp3", false, 1.0f, 1.0f, 1.0f);
            if (type == ui::Widget::TouchEventType::ENDED) {
                auto scene = SettingScene::create();
                Director::getInstance()->replaceScene(scene);
            }
        });

	auto shop = ResourceManager::GetInstance()->GetButtonById(2);


	shop->setPosition(Vec2(visibleSize.width /1.7, visibleSize.height / 2.3));

	shop->setScale(0.5);
	shop->removeFromParent();

	addChild(shop, 2);
	
	
   
   
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
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
