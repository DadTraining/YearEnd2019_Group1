
#include "GamePlay.h"
#include "cocos2d.h"

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

	// add diamond
	//AddDiamond();

	// update
	scheduleUpdate();

	return true;
}
void GamePlay::CreateMap()
{
		auto layer_1 = Layer::create();
		_tileMap = new CCTMXTiledMap();
		_tileMap->initWithTMXFile("map.tmx");

		_background = _tileMap->layerNamed("Background");
		_wall = _tileMap->layerNamed("MapLv1");
		//layer_1->addChild(_tileMap);
		this->addChild(_tileMap);
}

void GamePlay::InitialState()
{
	// initial state
	fight = false;

	// initial direction
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	jump = false;
}

void GamePlay::InitialObject()
{
	// setsubtestttttttttttttttttttt 

	// initial spider
	this->spider = new Spider(this);

	// initial main charactor
	this->main_charactor = new MainCharactor(this);
	this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
	CreateBloodBar();
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
		
}

void GamePlay::InitialPhysics()
{
	// ground
	Size layerSize = _wall->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _wall->getTileAt(Vec2(i, j));
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

bool GamePlay::OnContactBegin(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10 && nodeB->getTag() == 20)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);	
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 10)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 30)
		{
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 30 && nodeB->getTag() == 20)
		{
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 50)
		{
			//nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 50 && nodeB->getTag() == 20)
		{
			//nodeA->removeFromParentAndCleanup(true);
		}

		// fight
		else if (nodeA->getTag() == 60 && nodeB->getTag() == 10) {
			this->spider->SetBlood(this->spider->GetBlood() - 1);
		}
		else if (nodeA->getTag() == 10 && nodeB->getTag() == 60) {
			this->spider->SetBlood(this->spider->GetBlood() - 1);
		}
	}

	return true;
}

bool GamePlay::CheckPush()
{
	return true;
}

void GamePlay::CreateBloodBar()
	{
		Layer *layer_1 = Layer::create();
		auto bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
		bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
		bloodBar_1->setPercent(100);
		bloodBar_1->setPosition(Vec2(this->main_charactor->getVisibleSize().width / 2, this->main_charactor->getVisibleSize().height - 30));

		bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
		bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
		bloodBar_2->setPercent(this->main_charactor->GetBlood());
		bloodBar_2->setPosition(bloodBar_1->getPosition());

		this->addChild(bloodBar_1);
		this->addChild(bloodBar_2);
	}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
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
		case EventKeyboard::KeyCode::KEY_W:
		{
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

		// set view
		this->setViewPointCenter(main_charactor->GetSprite()->getPosition());

		// update blood
		bloodBar_2->setPercent(this->main_charactor->GetBlood());
	}	

void GamePlay::setViewPointCenter(CCPoint position)
	{
		CCSize winSize = Director::getInstance()->getVisibleSize();
		
		Vec2 mapMoveDistance = Vec2(0, 0);
		Vec2 mcMoveDistance = Vec2(0, 0);
		if (moveRight)
		{
			if (main_charactor->GetSprite()->getPosition().x < winSize.width / 2)
			{
				mcMoveDistance = Vec2(5, 0);
			}
			else
			{
				float mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width;
				if (_tileMap->getPosition().x > -(mapWidth - winSize.width - 5))
				{
					mapMoveDistance = -Vec2(5, 0);
				}
				else if (main_charactor->GetSprite()->getPosition().x <= (winSize.width - 5 - main_charactor->GetSprite()->getContentSize().width / 2))
				{
					mcMoveDistance = Vec2(5, 0);
				}
			}
		}
		else if (moveLeft)
		{
			if (main_charactor->GetSprite()->getPosition().x > winSize.width / 2)
			{
				mcMoveDistance = -Vec2(5, 0);
			}
			else
			{
				if (_tileMap->getPosition().x <= -5)
				{
					mapMoveDistance = Vec2(5, 0);
				}
				else if (main_charactor->GetSprite()->getPosition().x >= 5 + main_charactor->GetSprite()->getContentSize().width / 2)
				{
					mcMoveDistance = -Vec2(5, 0);
				}
			}
		}
		else if (jump)
		{
		
		if (main_charactor->GetSprite()->getPosition().y < winSize.height / 2)
		{
			mcMoveDistance = Vec2(0, 5);
		}
		else
		{
				
				float mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
				if (_tileMap->getPosition().y > -(mapHeight - winSize.height - 5))
				{
					mapMoveDistance = -Vec2(0, 5);
				}
				else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height - 5 - main_charactor->GetSprite()->getContentSize().height / 2))
				{
					mcMoveDistance = Vec2(0, 5);
				}
			}
		}
		else
		{
			if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
			{
				mcMoveDistance = -Vec2(0, 5);
			}
			else
			{
				if (_tileMap->getPosition().y <= -5)
				{
					mapMoveDistance = Vec2(0, 5);
				}
				else if (main_charactor->GetSprite()->getPosition().y >= 5 + main_charactor->GetSprite()->getContentSize().height / 2)
				{
					mcMoveDistance = -Vec2(0, 5);
				}
			}
		}

		if (mcMoveDistance != Vec2(0, 0))
		{
			main_charactor->GetSprite()->setPosition(main_charactor->GetSprite()->getPosition() + mcMoveDistance);
		}

		if (mapMoveDistance != Vec2(0, 0))
		{
			_tileMap->setPosition(_tileMap->getPosition() + mapMoveDistance);

			if(((Spider*)(spider))->isAlive())
			spider->GetSprite()->setPosition(spider->GetSprite()->getPosition() + mapMoveDistance);

			//rock->GetSprite()->setPosition(rock->GetSprite()->getPosition() + mapMoveDistance);
		}
	}	

GamePlay::GamePlay()
{
}		

GamePlay::~GamePlay()
{
}	
