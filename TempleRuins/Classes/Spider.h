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
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool isLeft;
	bool isRight;
	bool catogory;

	Scene* scene;
	Layer* layer;
	Action* action_up;
	Action* action_down;
	Action* action_side;
public:
	void Init();
	void InitialSPider();
	void InitialAction();
	void Update(float deltaTime);

	void SetState( bool moveLeft, bool moveRight, bool moveUp, bool moveDown);
	void SetCatogory(bool catogory);
	bool GetCatogory();

	void goUp();
	void goDown();
	void goSide();
	void goLeft();
	void goRight();

	void RotateLeft();
	void RotateRight();
	Spider(Layer* layer);
	Sprite* Clone(Sprite* sprite);
	~Spider();
};

