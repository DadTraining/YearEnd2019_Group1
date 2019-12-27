#pragma once
#include "Objject.h"

#define SPEED_FRAME_SPIDER 0.1f
#define SCALE_SPIDER 0.1
#define SPEED_ROTATE 0.01f

enum actions_spider {
	GO_UP,
	GO_DOWN,
	GO_LEFT,
	GO_RIGHT
};

class Spider : public Objject
{
private:
	bool isLeft;
	bool isRight;

	Scene* scene;
	Action* action_up;
	Action* action_down;
	Action* action_side;
public:
	void Init();
	void InitialSPider();
	void InitialAction();
	void Update(float deltaTime);
	void goUp();
	void goDown();
	void goSide();
	void goLeft();
	void goRight();

	void RotateLeft();
	void RotateRight();
	Spider(Scene* scene);
	~Spider();
};

