#include "Diamond.h"



Diamond::Diamond(Scene* scene)
{
	this->scene = scene;
	Init();
}


Diamond::~Diamond()
{
}

Sprite* Diamond::Clone(Sprite* sprite) 
{
	auto sprite_clone = Sprite::createWithTexture(sprite->getTexture());
	return sprite_clone;
}

void Diamond::Init() 
{
	this->SetSprite(Clone(ResourceManager::GetInstance()->GetSpriteById(3)));
	this->GetSprite()->setScale(SCALE_SPRITE);
	this->GetSprite()->setPosition(200, 200);
	this->scene->addChild(this->GetSprite());
}
void Diamond::Update(float deltaTime) 
{
}