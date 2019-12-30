
#include "GamePlay.h"
#include "cocos2d.h"

Size visibleSize;

Scene * GamePlay::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = GamePlay::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool GamePlay::init()
{
	if (!Scene::init())
	{
		return false;
	}


	//create map
	createMap();

	//init physics
	/*createPhysics();*/




	// initial state
	fight = false;

	// initial direction
	moveLeft = false;
	moveRight = false;

	moveUp = false;
	moveDown = false;
	jump = false;



	//// initial main charactor
	main_charactor = new MainCharactor(this);
	this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
	//this->setViewPointCenter(main_charactor->GetSprite()->getPosition());







	//// key board
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GamePlay::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GamePlay::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);


	// update
	scheduleUpdate();

	return true;
}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_J: {
		if (moveLeft || moveRight) {
			fight = false;
		}
		else {
			fight = true;
		}

		break;
	}
	case EventKeyboard::KeyCode::KEY_A: {
		moveLeft = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {
		moveRight = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_SPACE: {
		jump = true;
		break;
	}
	default:
		break;
	}
}

void GamePlay::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
		fight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_A: {
		moveLeft = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {
		moveRight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W: {
		jump = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		moveDown = false;
		break;
	}
	default:
		break;
	}
}

void GamePlay::update(float deltaTime)
{
	// update main charactor
	main_charactor->Update(deltaTime);
	((MainCharactor*)main_charactor)->setState(fight, moveLeft, moveRight, jump);
}

void GamePlay::setViewPointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (map->getMapSize().width * this->map->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (map->getMapSize().height * map->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void GamePlay::createMap()
{
	map = new CCTMXTiledMap();
	map->initWithTMXFile("map.tmx");

	backgroundLayer = map->layerNamed("Background");
	wallLayer = map->layerNamed("MapLv1");
	mObjectGroup = map->getObjectGroup("Objects");
	mPhysicsLayer = map->layerNamed("physics");
	mPhysicsLayer->setVisible(true);
	wallLayer->setVisible(false);

	addChild(map);
}

void GamePlay::createPhysics()
{
	//world
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	//ground
	Size layerSize = mPhysicsLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = mPhysicsLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setMass(100);
				tileSet->setPhysicsBody(physics);
			}
		}
	}
}

CCPoint GamePlay::tileCoorforposition(CCPoint position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;

	return ccp(x, y);
}

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}