#include "MiniGame.h"



MiniGame::MiniGame()
{
}


MiniGame::~MiniGame()
{
}



Scene * MiniGame::createMiniGame()
{
	return MiniGame::create();
}

bool MiniGame::init()
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

	moveLeft = false;
	moveRight = false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// draw
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// initial collect
	this->collect = 0;

	// initial item
	srand(time(NULL));
	for (int i = 0; i < NUM_ITEM; i++) {
		Objject* item = new Item_game(this);
		items.push_back(item);
	}

	// label collect
	CCString* colle = CCString::createWithFormat("%i", collect);
	label_Collect = Label::createWithTTF(colle->getCString(), "fonts/Marker Felt.ttf", 20);
	label_Collect->setPosition(10, 10);
	this->addChild(label_Collect);


	// initial time remain
	countTimmer = new CountTimer(this, TIME_REMAIN);


	auto move = MoveBy::create(1.0f, Vec2(0, 0));
	auto listener = EventListenerTouchOneByOne::create();
	/*listener->onTouchBegan = CC_CALLBACK_2(MiniGame::OnTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MiniGame::OnTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MiniGame::OnTouchEnded, this);*/
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	// initial time remain
	countTimmer = new CountTimer(this, TIME_REMAIN);


	// touch began
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MiniGame::OnTouhBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// test action pushhhhhhhhhhhhhhhhhhhhhhhhhh
	main_charac = new MainCharactor(this);

	// test rock
	Objject* rock = new Rock(this);

	// teest spider
	spider = new Spider(this);


	// key board
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(MiniGame::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(MiniGame::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);


	// update
	scheduleUpdate();

	return true;
}

bool MiniGame::OnTouhBegan(Touch * touch, Event * event)
{
	this->touch.x = touch->getLocation().x;
	this->touch.y = touch->getLocation().y;
	return false;
}

void MiniGame::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
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
	case EventKeyboard::KeyCode::KEY_W: {
		moveUp = true;
		run = true;
		wait = false;
		push = false;
		fight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		moveDown = true;
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

void MiniGame::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
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
	case EventKeyboard::KeyCode::KEY_W: {
		moveUp = false;
		wait = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		moveDown = false;
		wait = true;
		break;
	}
	default:
		break;
	}
}

void MiniGame::update(float deltaTime)
{
	// update item
	for (int i = 0; i < NUM_ITEM; i++) {
		((Item_game*)items[i])->SetTouch(touch);
		items[i]->Update(deltaTime);
		if (((Item_game*)items[i])->isCollect()) {
			collect++;
		}
	}

	// update collect
	CCString* colle = CCString::createWithFormat("%i", collect);
	label_Collect->setString(colle->getCString());

	// update count timer
	countTimmer->Update(deltaTime);

	// update main charactor
	main_charac->Update(deltaTime);

	//((MainCharactor*)main_charac)->setState(push, fight, wait, run, stun, moveLeft, moveRight);

	// update spider
	spider->Update(deltaTime);

	/*CCString* colle = CCString::createWithFormat("%i", collect);
	label_Collect->setString(colle->getCString());*/

}