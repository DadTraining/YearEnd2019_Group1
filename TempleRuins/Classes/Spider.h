#pragma once
#include "Objject.h"
class Spider : public Objject
{
private:
	Scene* scene;
	Animate* animate;
public:
	void Init();
	void Update(float deltaTime);
	Spider(Scene* scene);
	~Spider();
};

