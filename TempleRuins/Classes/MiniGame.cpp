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


	// touch began
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MiniGame::OnTouhBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

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
}