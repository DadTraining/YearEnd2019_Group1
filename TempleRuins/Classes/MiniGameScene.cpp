#include "MiniGameScene.h"
#include "SimpleAudioEngine.h"
#include "string.h"

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
	life = 3;

	// Meteor
	for (int i = 1; i <= 50; i++)
	{
			auto meteor = Sprite::create("aestroid_brown.png");
			meteor->setPosition(cocos2d::random(10, (int)visibleSize.width-10), cocos2d::random(visibleSize.height, (visibleSize.height * 10)));
			meteor->setTag(i);
			auto meteorBody = PhysicsBody::createCircle(meteor->getContentSize().width/2);
			meteor->setPhysicsBody(meteorBody);
			meteorBody->setDynamic(true);
			meteorBody->setVelocityLimit(300.0f);
			meteor->getPhysicsBody()->setContactTestBitmask(1);
			this->addChild(meteor);
	}

	// Diamond
	for (int i = 51; i <= 60; i++)
	{
		diamond = Sprite::create("CloseNormal.png");
		diamond->setPosition(cocos2d::random(10, (int)visibleSize.width - 10), cocos2d::random(visibleSize.height, (visibleSize.height * 10)));
		//diamond->setPosition(50 + (i * 10), 270);
		diamond->setTag(i);
		auto diamondBody = PhysicsBody::createCircle(diamond->getContentSize().width / 2);
		diamond->setPhysicsBody(diamondBody);
		diamondBody->setDynamic(true);
		diamondBody->setVelocityLimit(300.0f);
		diamond->getPhysicsBody()->setContactTestBitmask(1);
		this->addChild(diamond);
	}
	// Bar
	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(cocos2d::Size(visibleSize.width, 1), PhysicsMaterial(0.0f, 0.0f, 0.0f), 0);
	edgeSp->setPosition(Point(visibleSize.width / 2, -15));
	edgeSp->setPhysicsBody(boundBody);
	edgeSp->setTag(0);
	boundBody->setContactTestBitmask(1);
	this->addChild(edgeSp);

	// Label score
	CCString *tempScore = CCString::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 24);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setPosition(Point(15, visibleSize.height - 15));
	this->addChild(scoreLabel, 10000);

	// Label life
	CCString *tempLife = CCString::createWithFormat("%i", life);
	lifeLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 24);
	lifeLabel->setColor(Color3B::WHITE);
	lifeLabel->setPosition(Point(15, 15));
	this->addChild(lifeLabel, 10000);

	//  ===================Event diamond=================
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniGame::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ====================Event bar=====================
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MiniGame::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool MiniGame::onTouchBegan(Touch* touch, Event* event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 1; i <= 50; i++)
	{
		if (event->getCurrentTarget()->getChildByTag(i)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			if (this->life > 0)
			{
				this->life--;
			}
			auto hide = Hide::create();
			event->getCurrentTarget()->getChildByTag(i)->getPhysicsBody()->setEnabled(false);
			event->getCurrentTarget()->getChildByTag(i)->runAction(hide);
		}
	}
	for (int i = 51; i <= 60; i++)
	{
		if (event->getCurrentTarget()->getChildByTag(i)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			this->score++;
			event->getCurrentTarget()->getChildByTag(i)->getPhysicsBody()->setEnabled(false);
			//event->getCurrentTarget()->removeChildByTag(i, true);
			auto moveTo = MoveTo::create(2, Point(15, (int)visibleSize.height - 15));
			auto scaleBy = ScaleBy::create(2.0f, 0.3f);
			auto spawn = Spawn::createWithTwoActions(moveTo, scaleBy);
			auto hide = Hide::create();
			auto sequence = Sequence::create(spawn, hide, nullptr);
			event->getCurrentTarget()->getChildByTag(i)->runAction(sequence);
		}
	}
	return true;
}

bool MiniGame::onContactBegin(PhysicsContact &contact)
{
	auto hide = Hide::create();
	auto ObjA = contact.getShapeA()->getBody()->getNode();
	auto ObjB = contact.getShapeB()->getBody()->getNode();

	if (ObjA && ObjB)
	{
		if (ObjA->getTag() == 0)
		{
			ObjB->runAction(hide);
			ObjB->getPhysicsBody()->setEnabled(false);
		}
		else if (ObjB->getTag() == 0)
		{
			ObjA->runAction(hide);
			ObjB->getPhysicsBody()->setEnabled(false);
		}
	}

	//this->removeChild(ObjB, true);

	//this->removeChild(ObjA, true);

	return true;
}

void MiniGame::update(float deltaTime)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//===========Update score===============
	CCString *tempScore = CCString::createWithFormat("%i", score);
	scoreLabel->setString(tempScore->getCString());

	//===========Update life=======================
	CCString *tempLife = CCString::createWithFormat("%i", life);
	lifeLabel->setString(tempLife->getCString());
}