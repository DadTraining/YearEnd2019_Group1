#pragma once
#include "Objject.h"

#define SCALE_SPRITE 0.3

class Diamond :
	public Objject
{
private:
	Scene* scene;
public:
	Diamond(Scene* scene);
	Sprite* Clone(Sprite* sprite);
	~Diamond();
	void Init();
	void Update(float deltaTime);
};

