#include "MiniGameScene.h"

#define TagBar 1111
#define TagBall 1112


Scene* MiniGame::createScene()
{
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -500.0f));

	auto layer = MiniGame::create();

	layer->setPhyWorld(scene->getPhysicsWorld());
	
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool MiniGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// Create sprite ball and add it to the layer
	auto ball = Sprite::create("58-Breakout-Tiles.png");
	ball->setPosition(Point(visibleSize.width / 2, 20));
	ball->setScale(0.1f);
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	ballBody->setRotationEnable(false);
	ballBody->setMoment(0.0f);
	ballBody->setMass(0.0f);
	ballBody->setGravityEnable(false);
	ballBody->setDynamic(true);
	//ballBody->setVelocity(Vec2(cocos2d::random(0, 200), visibleSize.height));
	ballBody->setEnabled(false);
	ball->setPhysicsBody(ballBody);
	ball->getPhysicsBody()->setContactTestBitmask(1);
	//ball->setTag(100);
	this->addChild(ball, 2, TagBall);

	// Sprite bar
	auto bar = Sprite::create("50-Breakout-Tiles.png");
	bar->setPosition(Point(visibleSize.width / 2, 5));
	bar->setScale(0.1f);
	auto barBody = PhysicsBody::createBox(bar->getContentSize());
	barBody->setDynamic(false);
	bar->setPhysicsBody(barBody);
	this->addChild(bar, 1, TagBar);

	// Spite block
	for (int i = 1; i <= 3; ++i)
	{
		for (int j = 0; j < 10; j++)
		{
			auto block = Sprite::create("01-Breakout-Tiles.png");
			block->setPosition(Vec2(25 + (40 * j), 220 + (20 * i)));
			block->setScale(0.1f);
			this->addChild(block);
			auto blockBody = PhysicsBody::createBox(block->getContentSize());
			ballBody->setContactTestBitmask(0x1);
			block->setPhysicsBody(blockBody);
			blockBody->setDynamic(false);
			block->getPhysicsBody()->setContactTestBitmask(1);
		}
	}

	//
	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 1.0f, 0.0f), 0);
	edgeSp->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeSp->setPhysicsBody(boundBody); this->addChild(edgeSp); edgeSp->setTag(0);

	//  Khởi tạo một event cho bar
	auto listener = EventListenerTouchOneByOne::create();
	// Khi bạn nhấn xuống.
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		if (!event->getCurrentTarget()->getChildByTag(TagBall)->getPhysicsBody()->isEnabled())
		{
			event->getCurrentTarget()->getChildByTag(TagBall)->getPhysicsBody()->setEnabled(true);
			event->getCurrentTarget()->getChildByTag(TagBall)->getPhysicsBody()->setVelocity(Vec2(cocos2d::random(0, 200), Director::getInstance()->getVisibleSize().height));
		}
		return true;
	};

	// Khi bạn vừa nhấn xuống và di chuyển.
	listener->onTouchMoved = [](Touch* touch, Event* event) {
		Vec2 touchLocation = touch->getLocation();
		if (touchLocation.x >= 0 && touchLocation.x < Director::getInstance()->getVisibleSize().width)
		{
			//event->getCurrentTarget()->setPosition(Vec2(touchLocation.x, 5));
			event->getCurrentTarget()->getChildByTag(TagBar)->setPosition(Vec2(touchLocation.x, 5));
		}
	};

	// Khi bạn thả ra.
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		// Nơi chứa đoạn code của bạn.
	};

	// Thêm Touch Event vào cơ chế EventDispatch, sử dụng cơ chế ưu tiên Scene Graph
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MiniGame::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->setAccelerometerEnabled(true);

	return true;
}

void MiniGame::onAcceleration(Acceleration* acc, Event* unused_event)
{
	Vect gravity(-acc->y * 2000, acc->x * 2000);
	m_world->setGravity(gravity);
}

bool MiniGame::onContactBegin(PhysicsContact &contact)
{

	auto ObjA = contact.getShapeA()->getBody()->getNode();

	auto ObjB = contact.getShapeB()->getBody()->getNode();

	if (ObjA && ObjB)
	{
		if (ObjA->getTag() == TagBall)
		{
			ObjB->removeFromParentAndCleanup(true);
		}
		else if (ObjB->getTag() == TagBall)
		{
			ObjA->removeFromParentAndCleanup(true);
		}
	}

	//this->removeChild(ObjB, true);

	//this->removeChild(ObjA, true);

	return true;
}