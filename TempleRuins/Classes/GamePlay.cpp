#include "GamePlay.h"



Scene * GamePlay::createMiniGame()
{
	return GamePlay::create();
}

bool GamePlay::init()
{
	if (!Scene::initWithPhysics()) {
		return false;
	}

	// initial state
	push = false;
	fight = false;
	wait = false;
	run = false;
	stun = false;


	// initial direction
	moveLeft = false;
	moveRight = false;


	// initial main charactor
	this->main_charactor = new MainCharactor(this);


	// key board
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
		run = true;
		wait = false;
		push = false;
		fight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {
		moveRight = true;
		run = true;
		wait = false;
		push = false;
		fight = false;
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
		wait = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {
		moveRight = false;
		wait = true;
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

GamePlay::GamePlay()
{
}


GamePlay::~GamePlay()
{
}
