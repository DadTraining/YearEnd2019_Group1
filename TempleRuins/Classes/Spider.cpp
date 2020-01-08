#include "Spider.h"

void Spider::Init()
{

	// initial sprite
	InitialSPider();

	// initial action
	InitialAction();

}

void Spider::Update(float deltaTime)
{
	// true doc  false ngang

	if (GetCatogory()) {
		if (getSpiderMoveUp()) {
			this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(0, 130));
			/*auto moveby = MoveBy::create(2, Vec2(0, 130));
			this->GetSprite()->runAction(moveby);*/

		}else if (getSpiderMoveDown()) {
			this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(0, -130));
			/*auto moveby = MoveBy::create(2, Vec2(0, -130));
			this->GetSprite()->runAction(moveby);*/
		}
		
	}
	else {
		if(moveLeft)
		{
			RotateLeft();
			this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(-130, 0));
		}
		else if (moveRight) {
			RotateRight();
			this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(130, 0));
//			goRight();
		}
	}
}

Size Spider::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_SPIDER;
}

void Spider::InitialSPider()
{
	// initial blood
	this->SetBlood(BLOOD_SPIDER);

	// initial sprite
	this->SetSprite(Sprite::create("spider_01.png"));
	this->GetSprite()->setPosition(this->getVisibleSize() / 2);
	this->GetSprite()->setScale(SCALE_SPIDER);
	this->layer->addChild(this->GetSprite());
	this->GetSprite()->setTag(TAG_SPIDER);

	// physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(true);
	physicbody->setGravityEnable(false);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
	physicbody->setContactTestBitmask(true);
//	physicbody->setVelocity(Vec2(0,10));

	//
	
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

	// action right
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetSpiderSide(), SPEED_FRAME_SPIDER);
	action_side = RepeatForever::create(Animate::create(animation));
	action_side->setTag(actions_spider::GO_RIGHT);
	action_side->retain();
}

void Spider::goUp()
{
	this->GetSprite()->runAction(action_up);
	this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(0, 5));
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
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
//	this->UpdateVelocity(Vec2(posX - SPEED_RUN, posY));
	
//	this->GetSprite()->setPosition(posX - SPEED_RUN, posY);
	
}

void Spider::goRight()
{
	this->GetSprite()->setFlippedX(true);

}




void Spider::RotateLeft()
{
	if (!isLeft)
	{
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE_SPIDER, 0.0f, 180.f, rotatecallback);

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
		auto runaction = ActionFloat::create(SPEED_ROTATE_SPIDER, 180.f, 0.0f, rotatecallback);

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

Sprite * Spider::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	sprite_clone->retain();
	return sprite_clone;
}

Spider::~Spider()
{
}

void Spider::SetState( bool moveLeft, bool moveRight,  bool moveUp, bool moveDown)
{
	this->moveLeft = moveLeft;
	this->moveRight = moveRight;
	this->moveUp = moveUp;
	this->moveDown = moveDown;
}

void Spider::SetCatogory(bool catogory) 
{
	this->catogory = catogory; 
}

bool Spider::GetCatogory() 
{
	return this->catogory;
}

bool Spider::getSpiderMoveUp() 
{
	return this->moveUp;
}

bool Spider::getSpiderMoveDown()
{
	return this->moveDown;
}