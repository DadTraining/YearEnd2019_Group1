#include "MainCharactor.h"


MainCharactor::MainCharactor(Layer* layer)
{
	this->layer = layer;
	Init();
}

Sprite * MainCharactor::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}

MainCharactor::~MainCharactor()
{
}


void MainCharactor::setState(bool fight, bool moveLeft, bool moveRight, bool jump, bool stun, bool push, bool moveUp, bool moveDown)

{
	this->fight = fight;
	this->moveLeft = moveLeft;
	this->moveRight = moveRight;
	this->jump = jump;
	this->stun = stun;
	this->push = push;
	this->moveUp = moveUp;
	this->moveDown = moveDown;
}

void MainCharactor::Init()
{

	// initial state
	InitialState();

	// create sprite
	CreateSprite();

	// create animate action
	InitialAction();

	Wait();
}

void MainCharactor::InitialState()
{
	// check direction
	isLeft = false;
	isRight = true;

	// initial direction
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;

	// initial state
	push = false;
	fight = false;
	wait = true;
	run = false;
	stun = false;
	jump = false;
	jump_1 = false;
}

void MainCharactor::CreateSprite()
{
	// initial blood
	this->SetBlood(BLOOD_CHARACTOR);
	
	// create sprite
	auto main = Clone(ResourceManager::GetInstance()->GetSpriteById(3));
	this->SetSprite(main);
	main->setScale(SCALE_CHARACTOR);
	main->setPosition(550, 230);
	main->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->layer->addChild(main);   


	// create physic
	auto physicbody = PhysicsBody::createBox(main->getContentSize() - Size(0, 100));
	physicbody->setDynamic(true);
	physicbody->setGravityEnable(false);
	main->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setGravityEnable(false);

	main->getPhysicsBody()->setContactTestBitmask(1);
   	main->setTag(TAG_CHARACTOR); //tag dùng để xác định đối tượng va chạm
	this->GetSprite()->getPhysicsBody()->setLinearDamping(0.5f);

	// danh bua
	f = new FightHammer(30, 20, TAG_FIGHT);
	f->getFrameFight()->setPosition(-10, -10);
	this->layer->addChild(f->getFrameFight());
	f->getFrameFight()->getPhysicsBody()->setDynamic(false);
}

void MainCharactor::InitialAction()
{
	// push
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorPush(), SPEED_FRAME_CHARACTOR);
	action_push = Animate::create(animation);
	action_push->setTag(Actions::C_PUSH);
	action_push->retain();

	// wait
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorWait(), SPEED_FRAME_CHARACTOR);
	action_wait = Animate::create(animation);
	action_wait->setTag(Actions::C_WAIT);
	action_wait->retain();

	// run
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorRun(), SPEED_FRAME_CHARACTOR);
	action_run = RepeatForever::create(Animate::create(animation));
	action_run->setTag(Actions::C_RUN);
	action_run->retain();

	// fight
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorFight(), SPEED_FIGHT);
	action_fight = Animate::create(animation);
	action_fight->setTag(Actions::C_FIGHT);
	action_fight->retain();

	// stun
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorStun(), SPEED_FRAME_CHARACTOR);
	animate_stun = Animate::create(animation);
	animate_stun->retain();
	animate_stun->setTag(Actions::C_STUN);
}

void MainCharactor::Update(float deltaTime)
{
	if (fight && !(moveLeft || moveRight)) {
		if (!(fight && fight_1)) {
			Fight();
		}	
	}
	else if (moveLeft && !fight) {
		RotateLeft();
	}
	else if (moveRight && !fight) {
		RotateRight();
	}
	else {
		if ((this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0)) {
			Wait();
		}
	}
	if ((fight && fight_1) && (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0)) {
		Wait();
	}
	fight_1 = fight;
	jump_1 = jump;

	
	if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0) {
		f->getFrameFight()->setPosition(Vec2(-10, -10));

		/*if (isRight) {
			collis->getFrameFight()->setPosition(this->GetSprite()->getPosition() +
				ccp(this->getSize().width / 2 +
					collis->getSize().width / 2, 40));
		}
		else if (isLeft) {
			collis->getFrameFight()->setPosition(this->GetSprite()->getPosition() +
				ccp(-(this->getSize().width / 2 +
					collis->getSize().width / 2), 40));
		}*/
	}

	//this->GetSprite()->getPhysicsBody()->setVelocity(Vec2(50, 0));
}

void MainCharactor::Push()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0) {
		this->GetSprite()->stopAllActions();
	}
	if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_PUSH) == 0) {
		this->GetSprite()->runAction(action_push);
	}
}

void MainCharactor::Fight()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0) {
		this->GetSprite()->stopAllActions();
	}
	if(this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0)
	this->GetSprite()->runAction(action_fight);
}

void MainCharactor::Wait()
{
	if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_WAIT) == 0) {
		this->GetSprite()->stopAllActions();
		this->GetSprite()->runAction(action_wait);
	}
}

void MainCharactor::Run()
{
	if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_RUN) == 0) {
		this->GetSprite()->stopAllActions();
		this->GetSprite()->runAction(action_run);
	}
}

void MainCharactor::Stun()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0) {
		this->GetSprite()->stopAllActions();
	}

	this->GetSprite()->runAction(RepeatForever::create(animate_stun));
}

void MainCharactor::MoveLeft()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	//this->GetSprite()->setPosition(posX - SPEED_RUN, posY);
}

void MainCharactor::MoveRight()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX + SPEED_CHARACTOR_RUN, posY);
}

void MainCharactor::Jump()
{
	this->GetSprite()->getPhysicsBody()->applyImpulse(Vec2(0, 7000));
}

void MainCharactor::RotateLeft()
{
	Run();
	if (!isLeft) {
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE_CHARACTOR, 0.0f, 180.f, rotatecallback);

		//Run();
		this->GetSprite()->runAction(runaction);
	}
	isLeft = true;
	isRight = false;

	/*this->GetSprite()->setFlippedX(true);
	Run();*/
}

void MainCharactor::RotateRight()
{
	Run();
	if (!isRight) {
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE_CHARACTOR, 180.f, 0.0f, rotatecallback);
		//Run();
		this->GetSprite()->runAction(runaction);

	}
	isRight = true;
	isLeft = false;
	/*this->GetSprite()->setFlippedX(false);
	Run();*/
}

void MainCharactor::MoveUp()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX, posY + SPEED_CHARACTOR_RUN);
}

void MainCharactor::MoveDown()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX, posY - SPEED_CHARACTOR_RUN);
}

Size MainCharactor::getSize()
{
	return this->GetSprite()->getContentSize() * SCALE_CHARACTOR;
}

