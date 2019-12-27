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

	// create sprite
	auto main = Clone(ResourceManager::GetInstance()->GetSpriteById(3));
	this->SetSprite(main);
	main->setScale(SCALE_SPRITE);
	main->setPosition(200, 230);
	this->scene->addChild(main);   

	// create physic
	this->scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto physicbody = PhysicsBody::createBox(main->getContentSize());
	physicbody->setDynamic(true);
	main->setPhysicsBody(physicbody);
	physicbody->setRotationEnable(false);
	main->getPhysicsBody()->setContactTestBitmask(1);
   	main->setTag(100); //tag dùng để xác định đối tượng va chạm



	// create animate action
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

	Wait();
}

void MainCharactor::Update(float deltaTime)
{
	if (fight && !(moveLeft || moveRight)) {
		if (!(fight && fight_1)) Fight();
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
	float posX = this->GetSprite()->getPosition().x;
	float posY = this->GetSprite()->getPosition().y;
	if (posY < this->getVisibleSize().height) {
		auto moveBy = MoveBy::create(2, Vec2(0, posY + 10));
		this->GetSprite()->runAction(moveBy);
	}
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

