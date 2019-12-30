#include "Spider.h"

void Spider::Init()
{

	// initial sprite
	InitialSPider();

	// initial action
	InitialAction();

	goLeft();
}

void Spider::Update(float deltaTime)
{
	static bool check = true;
	static float i = 0;
	i += deltaTime;

	if (i >= 4)
	{
		check = !check;

		this->GetSprite()->stopAllActions();
		if (check)
		{
			//goDown();
			goLeft();
		}
		else
		{
			//goUp();
			goRight();
		}

		i = 0;
	}

	if (check)
	{
		this->GetSprite()->setPosition(this->GetSprite()->getPosition().x - 1, this->GetSprite()->getPosition().y);
	}
	else
	{
		this->GetSprite()->setPosition(this->GetSprite()->getPosition().x + 1, this->GetSprite()->getPosition().y);
	}
}

void Spider::InitialSPider()
{
	// initial blood
	this->SetBlood(BLOOD);

	// initial sprite
	this->SetSprite(Sprite::create("spider_01.png"));
	this->GetSprite()->setPosition(this->getVisibleSize() / 2);
	this->GetSprite()->setScale(SCALE_SPIDER);
	this->layer->addChild(this->GetSprite());
	this->GetSprite()->setTag(10);

	// physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
}

void Spider::InitialAction()
{
	// action up
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderUp(), SPEED_FRAME_SPIDER);
	action_up = RepeatForever::create(Animate::create(animation));
	action_up->setTag(actions_spider::GO_UP);
	action_up->retain();

	// action down
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderDown(), SPEED_FRAME_SPIDER);
	action_down = RepeatForever::create(Animate::create(animation));
	action_down->setTag(actions_spider::GO_DOWN);
	action_down->retain();

	// action left
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderSide(), SPEED_FRAME_SPIDER);
	action_side = RepeatForever::create(Animate::create(animation));
	action_side->setTag(actions_spider::GO_LEFT);
	action_side->retain();
}

void Spider::goUp()
{
	this->GetSprite()->runAction(action_up);
}

void Spider::goDown()
{
	this->GetSprite()->runAction(action_down);
}

void Spider::goSide()
{
	this->GetSprite()->runAction(action_side);
}

void Spider::goLeft()
{
	this->GetSprite()->runAction(action_side);
	this->GetSprite()->setFlippedX(false);
}

void Spider::goRight()
{
	this->GetSprite()->setFlippedX(true);
	this->GetSprite()->runAction(action_side);
}

void Spider::RotateLeft()
{
	if (!isLeft)
	{
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE, 0.0f, 180.f, rotatecallback);

		//Run();
		this->GetSprite()->runAction(runaction);
	}
	isLeft = true;
	isRight = false;
}

void Spider::RotateRight()
{
	if (!isRight)
	{
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE, 180.f, 0.0f, rotatecallback);

		this->GetSprite()->runAction(runaction);
	}
	isRight = true;
	isLeft = false;
}

Spider::Spider(Layer *layer)
{
	this->layer = layer;
	Init();
}

Spider::~Spider()
{
}
