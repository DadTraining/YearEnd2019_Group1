
#include "ResourceManager.h"
#include "LoadingLogo.h"
#include "SimpleAudioEngine.h"
#include <MainMenu.h>
#include "ui/CocosGUI.h"
#include "ControlMusic.h"
using namespace CocosDenshion;
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
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto logo = Sprite::create("play_pressed.png");
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /1.65);
	logo->setScale(0.33);
	addChild(logo);

	auto fadeInLogo = FadeIn::create(1.5f);
	auto fadeOutLogo = FadeOut::create(1.5f);
	logo->runAction(RepeatForever::create(Sequence::create(fadeInLogo, fadeOutLogo, nullptr)));



	//count = new CountTimer(this, TIME_LOAD);


	//this->schedule(schedule_selector(LoadingLogo::changeLoading), TIME_LOAD);



	auto loadingBarGB = Sprite::create("Load/bloodbar_bg.png");
	loadingBarGB->setPosition(Vec2(430, 150));
	loadingBarGB->setFlippedX(true);
	loadingBarGB->setScale(1.3);
	addChild(loadingBarGB,1);


	static auto loadingbar = ui::LoadingBar::create("Load/bloodbar.png");
	//loadingbar->setPosition(Vec2(385, 150));
	loadingbar->setPosition(loadingBarGB->getPosition());
	loadingbar->setScale(1.28);



	loadingbar->setPercent(0);
	
	loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);

	addChild(loadingbar,0);

	auto updateLoadingBar = CallFunc::create([]() {
		if (loadingbar->getPercent() < 100)
		{
			loadingbar->setPercent(loadingbar->getPercent() + 1);
		}
	});

	auto sequenceRunUpdateLoadingBar = Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.08f));
	auto repeat = Repeat::create(sequenceRunUpdateLoadingBar, 100);
	loadingbar->runAction(repeat);


	this->schedule(schedule_selector(LoadingLogo::changeLoading), 8.0f);
	
	//update

	
	return true;
}


void LoadingLogo::changeLoading(float dt) {
	auto Scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(
	TransitionFade::create(0.5, Scene));
}

void LoadingLogo::update(float deltaTime)
{
//count->Update(deltaTime);
}
