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
	//this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(3)));
	this->SetSprite(Sprite::create());
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(200, 200);
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
	//animate_fight->retain();
	//animate_fight->setTag(Actions::C_FIGHT);
	actionn = animate_fight;
	actionn->setTag(Actions::C_FIGHT);
	actionn->retain();
	
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
		Push();
	}
	else if (fight) {
		Fight(deltaTime);
	}
	else if (wait) {
		Wait();
	}
	else if (moveLeft) {
		RotateLeft();
		MoveLeft();
	}
	else if (moveRight) {
		RotateRight();
		MoveRight();
	}
	else {
		if (this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0)
			Wait();
		/*if (this->GetSprite()->getActionByTag(Actions::C_FIGHT) != nullptr) {
			if(this->GetSprite()->getActionByTag(Actions::C_FIGHT)->isDone())
			log("fa");
		}*/
	}
}


void MainCharactor::Push()
{

	
}

void MainCharactor::Fight(float deltaTime)
{
	
	if (this->GetSprite()->getNumberOfRunningActions() > 0) {
		this->GetSprite()->stopAllActions();
	}

	if(this->GetSprite()->getNumberOfRunningActionsByTag(Actions::C_FIGHT) == 0)
	this->GetSprite()->runAction(actionn);
};


void MainCharactor::Wait()
{
	//this->GetSprite()->stopAllActions();
	this->GetSprite()->runAction(RepeatForever::create(animate_wait));
	isLeft = false;
	isRight = false;
}

void MainCharactor::Run()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0) {
		this->GetSprite()->stopAllActions();
	}

	this->GetSprite()->runAction(RepeatForever::create(animate_run));
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
	this->GetSprite()->setPosition(posX - SPEED_RUN, posY);
}

void MainCharactor::MoveRight()
{
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX + SPEED_RUN, posY);
}

void MainCharactor::RotateLeft()
{
	if (!isLeft) {
		this->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
		auto rotatecallback = [=](float value) {
			this->GetSprite()->setRotation3D(Vec3(0, value, 0));
		};
		auto runaction = ActionFloat::create(SPEED_ROTATE, 0.0f, 180.f, rotatecallback);

		Run();
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
		

		Run();
		this->GetSprite()->runAction(runaction);

	}
	isRight = true;
	isLeft = false;
}


void MainCharactor::MoveUp() {
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX, posY + SPEED_RUN);
}
void MainCharactor::MoveDown() {
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	this->GetSprite()->setPosition(posX, posY - SPEED_RUN);
}

