
#include "GamePlay.h"



Scene * GamePlay::createGame()
{
	return GamePlay::create();
}


bool GamePlay::init()
{
	if (!Scene::initWithPhysics()) {
		return false;
	}

	// initial state
	fight = false;

	// initial direction
	moveLeft = false;
	moveRight = false;

	moveUp = false;
	moveDown = false;
	jump = false;



	// initial main charactor
	this->main_charactor = new MainCharactor(this);

	// initial spider
	this->spider = new Spider(this);

	// key board
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GamePlay::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GamePlay::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);



	//buttton move up
	auto buttonMoveUp = ui::Button::create("button.png");
	buttonMoveUp->setPosition(Vec2(100, 100));
	//button->setTitleText("Button Text");
	buttonMoveUp->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
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

	//button move down
	auto buttonMoveDown = ui::Button::create("button.png");
	buttonMoveDown->setPosition(Vec2(100, 50));
	//button->setTitleText("Button Text");
	buttonMoveDown->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			moveDown = true;
			fight = false;
			break;
		case ui::Widget::TouchEventType::ENDED:
			moveDown = false;
			break;
		default:
			break;
		}
	});
	addChild(buttonMoveDown);

	//button move left
	auto buttonMoveLeft = ui::Button::create("button.png");
	buttonMoveLeft->setPosition(Vec2(50, 50));
	//button->setTitleText("Button Text");
	buttonMoveLeft->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			moveLeft = true;
			/*run = true;
			wait = false;
			push = false;
			fight = false;*/
			break;
		case ui::Widget::TouchEventType::ENDED:
			moveLeft = false;
			//wait = true;
			break;
		default:
			break;
		}
	});
	addChild(buttonMoveLeft);

	//button move right
	auto buttonMoveRight = ui::Button::create("button.png");
	buttonMoveRight->setPosition(Vec2(150, 50));
	//button->setTitleText("Button Text");
	buttonMoveRight->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			moveRight = true;
			/*run = true;
			wait = false;
			push = false;
			fight = false;*/
			break;
		case ui::Widget::TouchEventType::ENDED:
			moveRight = false;
			//wait = true;
			break;
		default:
			break;
		}
	});
	addChild(buttonMoveRight);

	

	// update
	scheduleUpdate();

	return true;
}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
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
	case EventKeyboard::KeyCode::KEY_W: {
		jump = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		/*moveDown = true;
		run = true;
		wait = false;
		push = false;
		fight = false;*/

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

GamePlay::GamePlay()
{
}


GamePlay::~GamePlay()
{
}
