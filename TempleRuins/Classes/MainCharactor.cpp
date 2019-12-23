#include "MainCharactor.h"



MainCharactor::MainCharactor(Scene* scene)
{
	this->scene = scene;
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

void MainCharactor::SetAction(Actions action)
{
	this->action = action;
}


void MainCharactor::setState(bool push, bool fight, bool wait, bool run, bool stun, bool moveLeft, bool moveRight)
{
	this->push = push;
	this->fight = fight;
	this->wait = wait;
	this->run = run;
	this->stun = stun;

	this->moveLeft = moveLeft;
	this->moveRight = moveRight;
}

void MainCharactor::Init()
{
	// check direction
	isLeft = false;
	isRight = true;

	// initial direction
	moveLeft = false;
	moveRight = false;

	// initial state
	push = false;
	fight = false;
	wait = true;
	run = false;
	stun = false;

	// create sprite
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(3)));
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(200, 230);
	this->scene->addChild(this->GetSprite());   

	// create physic
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(false);
	this->GetSprite()->setPhysicsBody(physicbody);

	// create animate action
	// push
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorPush(), SPEED_FRAME);
	animate_push = Animate::create(animation);
	animate_push->retain();
	animate_push->setTag(Actions::C_PUSH);

	// wait
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorWait(), SPEED_FRAME);
	animate_wait = Animate::create(animation);
	animate_wait->retain();
	animate_wait->setTag(Actions::C_WAIT);

	// run
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorRun(), SPEED_FRAME);
	animate_run = Animate::create(animation);
	animate_run->retain();
	animate_run->setTag(Actions::C_RUN);

	// fight
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorFight(), SPEED_FRAME);
	animate_fight = Animate::create(animation);
	animate_fight->retain();
	animate_fight->setTag(Actions::C_FIGHT);

	// stun
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorStun(), SPEED_FRAME);
	animate_stun = Animate::create(animation);
	animate_stun->retain();
	animate_stun->setTag(Actions::C_STUN);

	Wait();
}

void MainCharactor::Update(float deltaTime)
{
	if (push) {
		//this->GetSprite()->stopAllActions();
		Push();
	}
	else if (fight) {
		//this->GetSprite()->stopAllActions();
		Fight();
	}
	else if (wait) {
		//this->GetSprite()->stopAllActions();
		Wait();
	}
	else if (run) {
		//this->GetSprite()->stopAllActions();
		Run();
	}
	else if (stun) {
		//this->GetSprite()->stopAllActions();
		Stun();
	}

	if (moveLeft) {	
		RotateLeft();
		MoveLeft();
	}
	else if (moveRight) {
		RotateRight();
		MoveRight();
	}
}


void MainCharactor::Push()
{
	//this->GetSprite()->stopActionByTag(Actions::C_PUSH);
	this->GetSprite()->stopAllActions();
	this->GetSprite()->runAction(RepeatForever::create(animate_push));
}

void MainCharactor::Fight()
{
	//this->GetSprite()->stopActionByTag(Actions::C_FIGHT);
	this->GetSprite()->stopAllActions();
	this->GetSprite()->runAction(RepeatForever::create(animate_fight));
}

void MainCharactor::Wait()
{
	//this->GetSprite()->stopActionByTag(Actions::C_WAIT);
	this->GetSprite()->stopAllActions();
	this->GetSprite()->runAction(RepeatForever::create(animate_wait));
}

void MainCharactor::Run()
{
	//this->GetSprite()->stopActionByTag(Actions::C_RUN);
	this->GetSprite()->stopAllActions();
	this->GetSprite()->runAction(RepeatForever::create(animate_run));
}

void MainCharactor::Stun()
{
	//this->GetSprite()->stopActionByTag(Actions::C_STUN);
	this->GetSprite()->stopAllActions();
	this->GetSprite()->runAction(RepeatForever::create(animate_stun));
}

void MainCharactor::MoveLeft()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX - SPEED_RUN, posY);
	Run();
	// set state
	/*push = false;
	fight = false;
	wait = false;
	run = true;
	stun = false;*/
}

void MainCharactor::MoveRight()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX + SPEED_RUN, posY);
	Run();
	// set state
	/*push = false;
	fight = false;
	wait = false;
	run = true;
	stun = false;*/
}

void MainCharactor::RotateLeft()
{
	if (!isLeft) {
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE, 0.0f, 180.f, rotatecallback);
		this->GetSprite()->runAction(runaction);
	}
	isLeft = true;
	isRight = false;
}

void MainCharactor::RotateRight()
{
	if (!isRight) {
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
