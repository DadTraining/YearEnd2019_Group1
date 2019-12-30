#pragma once
#include "Objject.h"
#define SCALE_OBJECT 0.3

class Rock : public Objject
{
private:
	Scene* scene;
public:
	void Init();
	void Update(float deltaTime);
	Rock(Scene* scene);
	Sprite* Clone(Sprite* sprite);
	~Rock();
};

