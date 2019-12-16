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

	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// initial item
	srand(time(NULL));
	for (int i = 0; i < NUM_ITEM; i++) {
		Objject* item = new Item_game(this);
		items.push_back(item);
	}

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
	for (int i = 0; i < NUM_ITEM; i++) {
		((Item_game*)items[i])->SetTouch(touch);
		items[i]->Update(deltaTime);
	}
}