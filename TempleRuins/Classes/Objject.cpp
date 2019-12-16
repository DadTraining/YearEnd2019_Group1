#include "Objject.h"



void Objject::SetBlood(int blood)
{
	this->blood = blood;
}

int Objject::GetBlood()
{
	return this->blood;
}

void Objject::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

Sprite * Objject::GetSprite()
{
	return this->sprite;
}

Objject::Objject()
{
}


Objject::~Objject()
{
}
