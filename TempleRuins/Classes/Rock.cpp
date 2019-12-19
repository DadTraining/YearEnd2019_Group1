#include "Rock.h"



void Rock::Init()
{
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(2)));
	this->GetSprite()->setScale(SCALE_OBJECT);
	auto physicsBody = PhysicsBody::createBox(this->GetSprite()->getContentSize());
	physicsBody->setDynamic(true);
	this->GetSprite()->setPosition(200, 200);
	this->GetSprite()->setPhysicsBody(physicsBody);
	this->scene->addChild(this->GetSprite());
}

void Rock::Update(float deltaTime)
{
}

Rock::Rock(Scene* scene)
{
	this->scene = scene;
	Init();
}

Sprite * Rock::Clone(Sprite * sprite)
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}


Rock::~Rock()
{
}
