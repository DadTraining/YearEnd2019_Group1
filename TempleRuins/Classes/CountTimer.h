#pragma once
#include "Objject.h"
class CountTimer : public Objject
{
private:
	int timeRemain;
	Scene* scene;
	Label* label_Timer;
public:
	void Init();
	void Update(float deltaTime);
	Sprite* Clone(Sprite* sprite);
	CountTimer(Scene* scene, int timeRemain);
	~CountTimer();
};

