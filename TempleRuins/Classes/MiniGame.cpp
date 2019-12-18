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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	// draw
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// initial collect
	//this->collect = 0;

	// initial item
	srand(time(NULL));
	for (int i = 0; i < NUM_ITEM; i++) {
		Objject* item = new Item_game(this);
		items.push_back(item);
	}

	// label collect
	/*CCString* colle = CCString::createWithFormat("%i", collect);
	label_Collect = Label::createWithTTF(colle->getCString(), "fonts/Marker Felt.ttf", 20);
	label_Collect->setPosition(10, 10);
	this->addChild(label_Collect);*/

	//// touch began
	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = CC_CALLBACK_2(MiniGame::OnTouhBegan, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto sprite = Sprite::create("mysprite.png");
	sprite->setScale(0.3);

	addChild(sprite);

	
	auto move = MoveBy::create(1.0f, Vec2(0,0));
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MiniGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MiniGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	


	// update
	scheduleUpdate();



	return true;
}

bool MiniGame::onTouchBegan(Touch* touch, Event* event)
{
	auto move = MoveTo::create(0.1f, touch->getLocation());
	this->runAction(move);
	return true;

}

bool MiniGame::onTouchEnded(Touch* touch, Event* event)
{
	auto move = MoveBy::create(0.1f, Vec2(0, 0));
	this->runAction(move->reverse());
	return true;
}

bool MiniGame::onTouchMoved(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	auto move = MoveTo::create(0, location);
	this->runAction(move);
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
	//update item
	for (int i = 0; i < NUM_ITEM; i++) {
		((Item_game*)items[i])->SetTouch(touch);
		items[i]->Update(deltaTime);
		if (((Item_game*)items[i])->isCollect()) {
			collect++;
		}
	}

	// update collect
	/*CCString* colle = CCString::createWithFormat("%i", collect);
	label_Collect->setString(colle->getCString());*/
}