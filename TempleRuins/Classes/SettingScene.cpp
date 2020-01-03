
# include "MainMenu.h"
# include "SettingScene.h"
# include "SimpleAudioEngine.h"
#include <ResourceManager.h>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
	return SettingScene::create();
}
// global variable
cocos2d::Vec2 originalSize;
float width;
float height;

// soundItems
LayerColor* layerSound;
// aboutItems
LayerColor* layerAbout;

bool SettingScene::init()
{
	srand((unsigned)time(0));
	if (!Scene::init()) {
		return false;
	}
	scheduleUpdate();
	originalSize = Director::getInstance()->getVisibleOrigin();
	width = Director::getInstance()->getVisibleSize().width / 2 + originalSize.x;
	height = Director::getInstance()->getVisibleSize().height / 2 + originalSize.y;
	auto background = ResourceManager::GetInstance()->GetBackgroundById(0);
	background->removeFromParent();
	addChild(background);
	background->setPosition(width ,height);

	// create soundItem
	createSound();
	// create scrollView
	createAbout();
	// add background
	
	SettingScene::addMenu();
	return true;
}



void SettingScene::addMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	
	auto returnButton = ui::Button::create("./button/Resume.png", " ");
	returnButton->setScale(0.5);
	returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			
			auto myScene = MainMenu::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene));
		});
	returnButton->setPosition(Vec2(visibleSize.width /8, visibleSize.height / 2));
	
	addChild(returnButton);
	

	auto label = Label::create("SETTING", "fonts/MarkerFelt.ttf", 50);
	label->enableGlow(Color4B::YELLOW);
	label->enableShadow();
	auto settingLabel = MenuItemLabel::create(label, nullptr);
	settingLabel->setPosition(width, height + 400);

	auto soundItem = MenuItemImage::create("./button/sound.png", " ",
		[&](Ref* pSender) {
			activeSound();
		});
	soundItem->setScale(0.5);
	soundItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /1.5));

	auto aboutItem = MenuItemImage::create("./button/about.png", " ",
		[&](Ref* pSender) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("./Sounds/sfx_clickbutton.wav", false, 1.0f, 1.0f, 1.0f);
			activeAbout();
		});
	aboutItem->setScale(0.5);
	aboutItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /2));

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[&](Ref* pSender) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("./Sounds/sfx_clickbutton.wav", false, 1.0f, 1.0f, 1.0f);
			exit(0);
		});

	closeItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	Vector<MenuItem*> menuItems;
	menuItems.pushBack(settingLabel);
	menuItems.pushBack(soundItem);
	menuItems.pushBack(aboutItem);
	menuItems.pushBack(closeItem);
	// Add menu
	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(0, 0);
	addChild(menu);
}



void SettingScene::createSound() {
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();
	
	layerSound = LayerColor::create(Color4B(20, 0, 0, 255));
	auto size = layerSound->getContentSize();
	layerSound->setContentSize(Size(size.width, size.height -200));
	layerSound->setVisible(false);
	layerSound->setPosition(0, 100);
	addChild(layerSound, 2);
	// create return button
	auto returnButton = ui::Button::create("./button/Resume.png", " ");
	layerSound->addChild(returnButton);
	returnButton->setPosition(Vec2(100, layerSound->getContentSize().height - 40));
	returnButton->setScale(0.5f);
	returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("./Sounds/sfx_clickbutton.wav", false, 1.0f, 1.0f, 1.0f);
			layerSound->setVisible(false);
		});



	auto label = Label::createWithSystemFont("SOUNDS", "Arial", 25);
	label->setPosition(Vec2(layerSound->getContentSize().width / 4.7, layerSound->getContentSize().height / 1.5));

	layerSound->addChild(label);

	static auto slider = ui::Slider::create();
	slider->loadBarTexture("slider_bar_bg.png");
	slider->loadSlidBallTextures("slider_ball_normal.png", "slider_ball_pressed.png", "slider_ball_disable.png");
	slider->loadProgressBarTexture("slider_bar_pressed.png");
	slider->setPercent(10);
	slider->setPosition(Vec2(layerSound->getContentSize().width / 2, layerSound->getContentSize().height / 1.5));
	slider->addClickEventListener([](Ref* event) {

		auto audio = SimpleAudioEngine::getInstance();
	
		audio->setEffectsVolume(0.5);
		audio->setBackgroundMusicVolume(0.5);
		log("Slider: %d", slider->getPercent());
	});
	layerSound->addChild(slider);





	/*auto label2 = Label::createWithSystemFont("MUSIC", "Arial", 25);
	label2->setPosition(Vec2(layerSound->getContentSize().width / 4.7, layerSound->getContentSize().height / 2.5));
	layerSound->addChild(label2);

	static auto slider2 = ui::Slider::create();
	slider2->loadBarTexture("slider_bar_bg.png");
	slider2->loadSlidBallTextures("slider_ball_normal.png", "slider_ball_pressed.png", "slider_ball_disable.png");
	slider2->loadProgressBarTexture("slider_bar_pressed.png");
	slider2->setPercent(10);
	slider2->setPosition(Vec2(layerSound->getContentSize().width / 2, layerSound->getContentSize().height /2.5));
	slider2->addClickEventListener([](Ref* event) {
		
		log("Slider: %d", slider2->getPercent());
	});
	layerSound->addChild(slider2);*/


}


void SettingScene::createAbout() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();

	layerAbout = LayerColor::create(Color4B(20, 0, 0, 255));
	auto size = layerAbout->getContentSize();
	layerAbout->setContentSize(Size(size.width, size.height - 200));
	layerAbout->setVisible(false);
	layerAbout->setPosition(0, 100);
	addChild(layerAbout, 2);
	
	auto returnButton = ui::Button::create("./button/Resume.png", " ");
	layerAbout->addChild(returnButton);
	returnButton->setPosition(Vec2(100, layerAbout->getContentSize().height - 40));
	returnButton->setScale(0.5f);
	returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
		
		auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("./Sounds/fire.wav", false, 1.0f, 1.0f, 1.0f);
			layerAbout->setVisible(false);
		});

	auto inSize = Vec2(layerAbout->getContentSize().width / 2, layerAbout->getContentSize().height / 2);
	auto label = Label::createWithSystemFont("Game Mysterious Temple Ruins", "Arial", 25);
	label->setPosition(inSize);
	
	layerAbout->addChild(label);



}



void SettingScene::activeAbout() {
	if (!layerAbout->isVisible()) {
		layerAbout->setVisible(true);
	}
	else {
		layerAbout->setVisible(false);
	}
}
void SettingScene::activeSound()
{
	if (!layerSound->isVisible()) {
		layerSound->setVisible(true);
	}
	else {
		layerSound->setVisible(false);
	}
}
void SettingScene::update(float deltaTime)
{

}

