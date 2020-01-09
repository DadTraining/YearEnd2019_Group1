

#include "MainMenu.h"
#include <ResourceManager.h>
#include "MapGame.h"
#include "ControlMusic.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace CocosDenshion;

ui::CheckBox* music_ui;
ui::CheckBox* sound_ui;
cocos2d::ui::Button* play;
cocos2d::ui::Button* setting;

Size visibleSize;
cocos2d::Sprite* mSettingLayer;
Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first

	srand((unsigned)time(0));
	if (!Scene::init()) {
		return false;
	}
	//scheduleUpdate();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = ResourceManager::GetInstance()->GetBackgroundById(0);
	background->removeFromParent();
	float scale = MAX(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setScale(scale);
	//background->setScale(0.2);
	addChild(background);
	background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 );

	auto turn = ControlMusic::GetInstance()->isMusic();
	if (turn == true)
	{
		auto audio = SimpleAudioEngine::getInstance();
		log("asd");
		audio->playBackgroundMusic("Sounds/menu.mp3", true);
		log("2");
	}
	createSetting();
	MainMenu::addButton();

    return true;
}

void MainMenu::addButton()
{
	//auto play = ResourceManager::GetInstance()->GetButtonById(0);
	play = ui::Button::create("play_normal.png", "play_pressed.png");
	play->setPosition(Vec2(230, 300));
	play->setScale(0.35);

	
	play->addClickEventListener([&](Ref* event)
	{ 
		
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("./Sounds/sfx_clickbutton.mp3", false);
		}
		Director::getInstance()->replaceScene(MapGame::create());
	});
	addChild(play);
	//auto setting = ResourceManager::GetInstance()->GetButtonById(1);
    setting = ui::Button::create("./button/ST.png", "./button/setting_pressed.png");
	setting->setPosition(Vec2(740,40));
	setting->setScale(0.5);
	setting->addClickEventListener([&](Ref* event)
	{  play->setVisible(false);
	   setting->setVisible(false);
		auto turn = ControlMusic::GetInstance()->isSound();
		if (turn == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			//log("asd");
			audio->playEffect("./Sounds/sfx_clickbutton.mp3", false);
			log("2");
		}
		activeSetting();
	});
	addChild(setting);

}

void MainMenu::createSetting()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	mSettingLayer = Sprite::create("./setting/table.png");
	auto size = mSettingLayer->getContentSize();
	mSettingLayer->setContentSize(Size(400,400));
	mSettingLayer->setVisible(false);
	mSettingLayer->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(mSettingLayer,2);
	
	auto returnButton = ui::Button::create("./setting/close_2.png", "");
	mSettingLayer->addChild(returnButton,3);
	returnButton->setPosition(Vec2(360,367));
	returnButton->setScale(0.65f);

	returnButton->addClickEventListener([&](Ref* event)
	{
		play->setVisible(true);
		setting->setVisible(true);
		auto turn = ControlMusic::GetInstance()->isSound();
	if (turn == true)
	{
		auto audio = SimpleAudioEngine::getInstance();
		//log("asd");
		audio->playEffect("./Sounds/sfx_clickbutton.mp3", false);
		log("2");
	}
	mSettingLayer->setVisible(false);
	});

	auto musiclb = Label::create("MUSIC", "./fonts/Arial",22);
	musiclb->setPosition(120,250);
	musiclb->setColor(Color3B::BLACK);
	mSettingLayer->addChild(musiclb, 4);

	 music_ui = ui::CheckBox::create("setting/95.png", "setting/96.png");
	music_ui->setScale(0.588f);
	//music_ui->retain();
	music_ui->setSelected(ControlMusic::GetInstance()->isMusic());
	music_ui->addClickEventListener([&](Ref* event)
	{
		music_ui->isSelected();

		if (!music_ui->isSelected())
		{
			ControlMusic::GetInstance()->setMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/menu.mp3", true);
		}
		else
		{
			ControlMusic::GetInstance()->setMusic(false);   	
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	});
	music_ui->setPosition(musiclb->getPosition() + Vec2(140, 0));
	music_ui->setEnabled(true);
	mSettingLayer->addChild(music_ui, 4);

	auto soundlb = Label::create("SOUND","./fonts/Arial", 22);
	soundlb->setPosition(120, 170);
	soundlb->setColor(Color3B::BLACK);
	//soundlb->retain();
	mSettingLayer->addChild(soundlb, 4);

	 sound_ui = ui::CheckBox::create("./setting/95.png","./setting/96.png");
	sound_ui->retain();
	sound_ui->setScale(0.58f);
	sound_ui->setSelected(ControlMusic::GetInstance()->isSound());
	sound_ui->addClickEventListener([&](Ref* event)
	{		//sound_ui->isSelected();
	if (!sound_ui->isSelected())
	{
	ControlMusic::GetInstance()->setSound(true);
	}
	else
	{
	ControlMusic::GetInstance()->setSound(false);
	SimpleAudioEngine::getInstance()->stopAllEffects();

	}
	
	});
	sound_ui->setPosition(soundlb->getPosition() + Vec2(140, 0));
	sound_ui->setEnabled(true);
	mSettingLayer->addChild(sound_ui,4);


}

void MainMenu::activeSetting() {
	if (!mSettingLayer->isVisible()) {
		mSettingLayer->setVisible(true);
	}
	else {
		mSettingLayer->setVisible(false);
	}
}


void MainMenu::update(float deltaTime)
{
}
