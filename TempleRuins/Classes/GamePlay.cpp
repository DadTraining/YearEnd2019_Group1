
#include "GamePlay.h"
#include "cocos2d.h"

Size visibleSize;

Scene *GamePlay::createGame()
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
	if (!Layer::init())
	{
		return false;
	}

	// create map
	CreateMap();

	// initial physics for map
	InitialPhysics();

	// initial state
	InitialState();

	// initial object
	InitialObject();

	// add dispatcher
	AddDispatcher();

	// add button
	InitialButton();

	// update
	scheduleUpdate();

	return true;
}

void GamePlay::CreateMap()
{
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
	jump = false;
}

void GamePlay::InitialState()
{
	fight = false;
	moveLeft = false;
	moveRight = false;
	moveUp = false;
		jump = false;
}

//// initial main charactor

void GamePlay::InitialObject()
{
	// initial main charactor
	this->main_charactor = new MainCharactor(this);
	this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());

	CreateBloodBar();

	// initial spider
	this->spider = new Spider(this);
	this->setViewPointCenter(this->spider->GetSprite()->getPosition());
}

void GamePlay::AddDispatcher()
{
	// key board

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GamePlay::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GamePlay::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	// listener contact
	auto contacListener = EventListenerPhysicsContact::create();
	contacListener->onContactBegin = CC_CALLBACK_1(GamePlay::OnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contacListener, this);
}

void GamePlay::InitialButton()
{
	//buttton move up
	auto buttonMoveUp = ui::Button::create("button.png");
	buttonMoveUp->setPosition(Vec2(100, 100));
	buttonMoveUp->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			moveUp = true;
			fight = false;
			break;
		case ui::Widget::TouchEventType::ENDED:
			moveUp = false;
			break;
		default:
			break;
		}
	});
	addChild(buttonMoveUp);

	//button move left
	auto buttonMoveLeft = ui::Button::create("button.png");
	buttonMoveLeft->setPosition(Vec2(50, 50));
	buttonMoveLeft->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			moveLeft = true;
			break;
		case ui::Widget::TouchEventType::ENDED:
			moveLeft = false;
			break;
		default:
			break;
		}
	});
	addChild(buttonMoveLeft);

	//button move right
	auto buttonMoveRight = ui::Button::create("button.png");
	buttonMoveRight->setPosition(Vec2(150, 50));
	buttonMoveRight->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			moveRight = true;
			break;
		case ui::Widget::TouchEventType::ENDED:
			moveRight = false;
			break;
		default:
			break;
		}
	});
	addChild(buttonMoveRight);
}

void GamePlay::InitialPhysics()
{ //test
	// ground
	auto _frame = _tileMap->layerNamed("physics");
	Size layerSize = _frame->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _frame->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physic = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				physic->setMass(100);
				tileSet->setPhysicsBody(physic);
			}
		}
	}
}

bool GamePlay::OnContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10 && nodeB->getTag() == 20)
		{
			if (!fight)
				this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
			else if (CheckFight())
				log("danh1");
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 10)
		{
			if (!fight)
				this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
			else if (CheckFight())
				log("danh2");
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 30)
		{
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 30 && nodeB->getTag() == 20)
		{
			nodeA->removeFromParentAndCleanup(true);
		}
	}

	return true;
}

bool GamePlay::CheckFight()
{
	float ySpider = this->spider->GetSprite()->getPosition().y;
	float yCharac = this->main_charactor->GetSprite()->getPosition().y;
	float ySpiderSize = this->spider->GetSprite()->getContentSize().height;
	float yCharacSize = this->main_charactor->GetSprite()->getContentSize().height;

	/*if (fight && (yCharac > ySpider - (ySpiderSize / 2) && yCharac < ySpider + (ySpiderSize / 2))) {
		return true;
	}*/
	if (fight)
		return true;

	return false;
}

void GamePlay::CreateBloodBar()
{
	Layer *layer_1 = Layer::create();
	auto bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_1->setPercent(100);
	bloodBar_1->setPosition(Vec2(this->main_charactor->getVisibleSize().width / 2, this->main_charactor->getVisibleSize().height - 30));

	auto bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
	bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
	bloodBar_2->setPercent(this->main_charactor->GetBlood());
	bloodBar_2->setPosition(bloodBar_1->getPosition());

	layer_1->addChild(bloodBar_1);
	layer_1->addChild(bloodBar_2);
	this->addChild(layer_1);
}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_J:
	{
		if (moveLeft || moveRight)
		{
			fight = false;
		}
		else
		{
			fight = true;
		}

		break;
	}

	case EventKeyboard::KeyCode::KEY_A:
	{
		moveLeft = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		moveRight = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		jump = true;
		break;
	}
	default:
		break;
	}
}

void GamePlay::OnKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		fight = false;
		break;
	}

	case EventKeyboard::KeyCode::KEY_A:
	{
		moveLeft = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		moveRight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		jump = false;
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
	((MainCharactor *)main_charactor)->setState(fight, moveLeft, moveRight, jump);

	// update spider
	spider->Update(deltaTime);

	this->setViewPointCenter(main_charactor->GetSprite()->getPosition());
}

void GamePlay::setViewPointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
	//_tileMap->setPosition(viewPoint);
}

void GamePlay::createMap()
{
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map.tmx");

	backgroundLayer = _tileMap->layerNamed("Background");
	wallLayer = _tileMap->layerNamed("MapLv1");
	mObjectGroup = _tileMap->getObjectGroup("Objects");
	mPhysicsLayer = _tileMap->layerNamed("physics");
	mPhysicsLayer->setVisible(true);
	wallLayer->setVisible(false);

	addChild(_tileMap);
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
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;

	return ccp(x, y);
}

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}
