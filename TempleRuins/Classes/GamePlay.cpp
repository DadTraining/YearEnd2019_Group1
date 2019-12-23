#include "GamePlay.h"
#include "cocos2d.h"


//bool left = false;
//bool right = false;
//bool up = false;
//bool down = false;

Scene * GamePlay::createGame()
{
	return GamePlay::create();
}

bool GamePlay::init()
{
	if (!Scene::initWithPhysics()) {
		return false;
	}

	//create map
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map.tmx");

	_background = _tileMap->layerNamed("Background");
	this->addChild(_tileMap);

	//// initial state
	push = false;
	fight = false;
	wait = false;
	run = false;
	stun = false;


	//// initial direction
	moveLeft = false;
	moveRight = false;


	//// initial main charactor
	this->main_charactor = new MainCharactor(this);
	this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());

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
	case EventKeyboard::KeyCode::KEY_UP_ARROW: {
		push = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
		fight = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
		wait = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		run = true;
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
	default:
		break;
	}
}

void GamePlay::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW: {
		push = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
		fight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
		wait = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
		run = false;
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
	default:
		break;
	}
}

void GamePlay::update(float deltaTime)
{
	// update main charactor
	main_charactor->Update(deltaTime);
	((MainCharactor*)main_charactor)->setState(push, fight, wait, run, stun, moveLeft, moveRight);
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
}



GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}
