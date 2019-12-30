
# include "SettingScene.h"
# include "SimpleAudioEngine.h"
#include <ResourceManager.h>

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


	
	auto returnButton = ui::Button::create("resume_normal.png", "resume_pressed.png");
	returnButton->setScale(0.5);
	returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			
			auto myScene = MainMenu::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene));
		});
	returnButton->setPosition(Vec2(visibleSize.width /3.3, visibleSize.height / 3));
	addChild(returnButton);
	

	auto label = Label::create("SETTING", "fonts/MarkerFelt.ttf", 50);
	label->enableGlow(Color4B::YELLOW);
	label->enableShadow();
	auto settingLabel = MenuItemLabel::create(label, nullptr);
	settingLabel->setPosition(width, height + 400);

	auto soundItem = MenuItemImage::create("./button/btSound.png", " ",
		[&](Ref* pSender) {
			activeSound();
		});
	soundItem->setScale(0.2);
	soundItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /1.5));

	auto aboutItem = MenuItemImage::create("./button/btAbout.png", " ",
		[&](Ref* pSender) {
			activeAbout();
		});
	aboutItem->setScale(0.2);
	aboutItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /2));

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[&](Ref* pSender) {
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
	auto returnButton = ui::Button::create("resume_normal.png", "resume_pressed.png");
	layerSound->addChild(returnButton);
	returnButton->setPosition(Vec2(100, layerSound->getContentSize().height - 40));
	returnButton->setScale(0.5f);
	returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			layerSound->setVisible(false);
		});




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
	
	auto returnButton = ui::Button::create("resume_normal.png", "resume_pressed.png");
	layerAbout->addChild(returnButton);
	returnButton->setPosition(Vec2(100, layerAbout->getContentSize().height - 40));
	returnButton->setScale(0.5f);
	returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			layerAbout->setVisible(false);
		});

	auto scrollView = ui::ScrollView::create();
	layerAbout->addChild(scrollView);
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setPosition(Vec2(100,50));
	scrollView->setContentSize(Size(300,300));
	scrollView->setBounceEnabled(true);

	auto inSize = Vec2(scrollView->getContentSize().width / 2, scrollView->getContentSize().height / 2);
	auto label = Label::createWithSystemFont("Game Mysterious Temple Ruins", "Arial", 25);
	label->setPosition(inSize);
	
	scrollView->addChild(label);



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

