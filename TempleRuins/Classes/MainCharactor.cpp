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



void MainCharactor::setState(bool fight, bool moveLeft, bool moveRight, bool jump)
{
	this->fight = fight;
	this->moveLeft = moveLeft;
	this->moveRight = moveRight;
	this->jump = jump;
}

void MainCharactor::Init()
{
	// khung  -> qua gameplay
	auto edgeBody = PhysicsBody::createEdgeBox(this->getVisibleSize());
	auto edgeNode = Node::create();
	edgeNode->setPosition(this->getVisibleSize() / 2);
	this->scene->addChild(edgeNode);
	edgeNode->setPhysicsBody(edgeBody);

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
	this->SetBlood(BLOOD);
	CreateBloodBar();

	// create sprite
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(3)));
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(300, 230);
	this->scene->addChild(this->GetSprite());
	this->GetSprite()->setTag(20);

	// create physic
	this->scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto physicbody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicbody->setDynamic(true);
	this->GetSprite()->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	physicbody->setContactTestBitmask(1);
	this->GetSprite()->getPhysicsBody()->setLinearDamping(0.5f);
}

void MainCharactor::InitialAction()
{
	// push
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorPush(), SPEED_FRAME);
	animate_push = Animate::create(animation);
	animate_push->retain();
	animate_push->setTag(Actions::C_PUSH);

	// wait
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorWait(), SPEED_FRAME);
	action_wait = Animate::create(animation);
	action_wait->setTag(Actions::C_WAIT);
	action_wait->retain();

	// run
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorRun(), SPEED_FRAME);
	action_run = RepeatForever::create(Animate::create(animation));
	action_run->setTag(Actions::C_RUN);
	action_run->retain();

	// fight
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorFight(), SPEED_FIGHT);
	action_fight = Animate::create(animation);
	action_fight->setTag(Actions::C_FIGHT);
	action_fight->retain();

	// stun
	animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetCharactorStun(), SPEED_FRAME);
	animate_stun = Animate::create(animation);
	animate_stun->retain();
	animate_stun->setTag(Actions::C_STUN);
}

void MainCharactor::CreateBloodBar()
{
	auto bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_1->setPercent(100);
	bloodBar_1->setPosition(Vec2(this->getVisibleSize().width / 2, this->getVisibleSize().height - 30));

	bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
	bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
	bloodBar_2->setPercent(this->GetBlood());
	bloodBar_2->setPosition(bloodBar_1->getPosition());

	this->scene->addChild(bloodBar_1);
	this->scene->addChild(bloodBar_2);
}

void MainCharactor::UpdateBloodBar()
{
	this->bloodBar_2->setPercent(this->GetBlood());
}


void MainCharactor::Update(float deltaTime)
{
	if (fight && !(moveLeft || moveRight)) {
		if(!(fight && fight_1)) Fight();
	}
	else if (moveLeft && !fight) {
		RotateLeft();
		MoveLeft();
	}
	else if (moveRight && !fight) {
		RotateRight();
		MoveRight();
	}
	else if (!(jump && jump_1) && (jump != jump_1)) {
		Jump();
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

	UpdateBloodBar(); //update blood
}


void MainCharactor::Push()
{

	
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
	
	isLeft = false;
	isRight = false;
}

void MainCharactor::Run()
{
	if (this->GetSprite()->getNumberOfRunningActions() > 0) {
		this->GetSprite()->stopAllActions();
	}

	this->GetSprite()->runAction(action_run);
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

void MainCharactor::Jump()
{
	this->GetSprite()->getPhysicsBody()->applyImpulse(Vec2(0, 5000));
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

	/*this->GetSprite()->setFlippedX(true);
	Run();*/
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

	/*this->GetSprite()->setFlippedX(false);
	Run();*/
}
