#include "Spider.h"



void Spider::Init()
{
	// initial sprite
	this->SetSprite(Sprite::create());
	this->GetSprite()->setPosition(300, 200);
	this->GetSprite()->setScale(SCALE_SPIDER);
	this->scene->addChild(this->GetSprite());

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


	goSide();
}

void Spider::Update(float deltaTime)
{
	static bool check = true;
	static float i = 0;
	i += deltaTime;
	

	if (i >= 2) {
		check = !check;
	
		this->GetSprite()->stopAllActions();
		if (check) {
			goDown();
		}
		else {
			goUp();
		}

		i = 0;
	}
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
}

void Spider::goRight()
{
}


void Spider::RotateLeft()
{
	if (!isLeft) {
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
	if (!isRight) {
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE, 180.f, 0.0f, rotatecallback);


		//Run();
		this->GetSprite()->runAction(runaction);

	}
	isRight = true;
	isLeft = false;
}

Spider::Spider(Scene* scene)
{
	this->scene = scene;
	Init();
}


Spider::~Spider()
{
}
