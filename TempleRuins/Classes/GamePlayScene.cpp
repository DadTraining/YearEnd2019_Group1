#include "GamePlayScene.h"



Scene * GamePlayScene::createScene()
{
	return GamePlayScene::create();
}

bool GamePlayScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (!Scene::init())
	{
		return false;
	}

	auto map1 = TMXTiledMap::create("map.tmx");
	this->addChild(map1,-1);

	auto point = map1->getObjectGroup("Charac");
	point->getObject("CharacPoint");
	if (point == NULL)
	{
		return false;
	}

	/*float x = point->getProperty("X").asFloat();
	float y = point->getProperty("Y").asFloat();*/

	//auto mainCharactor = Sprite::create("Sprite/1.png");
	//mainCharactor->setPosition(Vec2(0,0));
	//mainCharactor->setScale(0.1);
	//this->addChild(mainCharactor);
}

void GamePlayScene::update(float deltaTime)
{
}

GamePlayScene::GamePlayScene()
{
}


GamePlayScene::~GamePlayScene()
{
}
