
# include "MainMenu.h"
# include "SettingScene.h"
# include "SimpleAudioEngine.h"
#include <ResourceManager.h>
#include "SimpleAudioEngine.h"
#include "ControlMusic.h"
#include "ui/CocosGUI.h"
using namespace CocosDenshion;
ui::Slider* volumeSlider;
ui::CheckBox* sound;
ui::CheckBox* music;
Scene* SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	srand((unsigned)time(0));
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("./setting/bb.jpg");
	background->removeFromParent();
	float scale = MAX(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setScale(scale);
	//background->setScale(0.2);
	addChild(background);
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	
	auto bg = Sprite::create("./setting/table.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg->setScale(0.25);
	bg->retain();
	addChild(bg, 1);
	auto musiclb = Label::create("MUSIC", "./fonts/Arial", 24);
	musiclb->setPosition(bg->getPosition() + Vec2(-88, 70));
	musiclb->setColor(Color3B::BLACK);
	addChild(musiclb, 2);

	auto music = ui::CheckBox::create("./setting/95.png", "./setting/96.png");
	music->setPosition(musiclb->getPosition() + Vec2(155, 0));
	music->setScale(0.6f);
	music->retain();
	music->setSelected(ControlMusic::GetInstance()->isMusic());
	music->addClickEventListener([&](Ref* event)
	{
		if (!music->isSelected())
		{
			ControlMusic::GetInstance()->setMusic(true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic("./Sounds/menu.mp3", true);
		}
		else
		{
			ControlMusic::GetInstance()->setMusic(false);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	});
	music->setEnabled(true);
	addChild(music, 3);

	/*auto soundlb = Label::create("SOUND", "./fonts/Arial", 24);
	soundlb->setPosition(bg->getPosition() + Vec2(-83,20));
	soundlb->setColor(Color3B::BLACK);
	soundlb->retain();
	addChild(soundlb, 2);

	auto sound = ui::CheckBox::create("./setting/95.png", "./setting/96.png");
	sound->setPosition(soundlb->getPosition() + Vec2(150, 0));
	sound->retain();
	sound->setScale(0.6f);
	sound->setSelected(ControlMusic::GetInstance()->isSound());
	sound->addClickEventListener([&](Ref* event)
	{
		sound->isSelected();
		if (!sound->isSelected())
		{
			ControlMusic::GetInstance()->setSound(true);

		}
		else
		{
			ControlMusic::GetInstance()->setSound(false);
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}

	});
	sound->setEnabled(true);
	addChild(sound, 3);
	
	*/

	auto close = ui::Button::create("./setting/close_2.png","");
	close->setPosition(Vec2(235,405));
	close->setScale(0.8);
	addChild(close,3);
	close->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{ 
		auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("./Sounds/sfx_clickbutton.wav", false);
	if (type == ui::Widget::TouchEventType::ENDED) {
		auto scene = MainMenu::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	});
	
	return true;
}
	



void SettingScene::update(float deltaTime)
{

}

