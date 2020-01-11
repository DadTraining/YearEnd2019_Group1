#include "GamePlay2.h"

Scene * GamePlay2::createGame()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setSubsteps(8);

	// 'layer' is an autorelease object
	auto layer = GamePlay2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GamePlay2::init()
{
	//create Map
	createMap();

	//create physics for Map
	createMapPhysics();

	// update
	scheduleUpdate();

	return true;
}

void GamePlay2::update(float deltaTime)
{
}

void GamePlay2::createMap()
{
	//auto layer_1 = Layer::create();
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map2.tmx");
	_tileMap->setScale(2.0);
	_background = _tileMap->layerNamed("Background");
	_wall = _tileMap->layerNamed("MapLv2");
	_phy = _tileMap->layerNamed("physics");
	_phy->setVisible(false);
	mObjectGroup = _tileMap->getObjectGroup("Objects");
	this->addChild(_tileMap);
}

void GamePlay2::createMapPhysics()
{
	Size layerSize = _phy->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _phy->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physic = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				physic->setMass(100);
				tileSet->setPhysicsBody(physic);
				tileSet->setTag(TAG_MAP);
			}
		}
	}
}

GamePlay2::GamePlay2()
{
}

GamePlay2::~GamePlay2()
{
}
