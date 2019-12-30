#pragma once
#include "Objject.h"
#define SCALE_OBJECT 0.3

class Rock : public Objject
{
private:
	Layer* layer;
public:
	void Init();
	void Update(float deltaTime);
	Rock(Layer* layer);
	Sprite* Clone(Sprite* sprite);
	~Rock();
};

