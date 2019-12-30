#pragma once
#include "Objject.h"

enum actions_spider {
	GO_UP,
	GO_DOWN,
	GO_LEFT,
	GO_RIGHT
};

class Spider : public Objject
{
private:
	Scene* scene;
	Animate* animate_up;
	Animate* animate_down;
	Animate* animate_left;
	Animate* animate_right;
public:
	void Init();
	void Update(float deltaTime);
	void goUp();
	void goDown();
	void goLeft();
	void goRight();
	Spider(Scene* scene);
	~Spider();
};

