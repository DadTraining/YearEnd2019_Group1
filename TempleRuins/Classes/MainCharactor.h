#pragma once
#include "Objject.h"
#include "Box2D/Box2D.h"

#define SCALE_SPRITE 0.15
#define SPEED_FRAME 0.2f
#define SPEED_FIGHT 0.2f
#define SPEED_RUN 3
#define SPEED_ROTATE 0.01f

enum Actions {
	C_PUSH,
	C_FIGHT,
	C_WAIT,
	C_RUN,
	C_STUN
};

class MainCharactor : public Objject
{
private:
	bool isLeft;
	bool isRight;

	bool push;
	bool fight;
	bool fight_1 = false;
	bool wait;
	bool run;
	bool stun;
	bool jump;
	bool jump_1;

	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;

	Actions action;
	Scene* scene;
	Animate* animate_push;
	Animate* animate_stun;

	Action *action_fight;
	Action *action_wait;
	Action *action_run;
public:
	void SetAction(Actions action);

	void setState(bool fight, bool moveLeft, bool moveRight, bool jump);
	void Init();
	void Update(float deltaTime);
	void Push();
	void Fight();
	void Wait();
	void Run();
	void Stun();
	void MoveLeft();
	void MoveRight();
	void Jump();

	void MoveUp();
	void MoveDown();
	void RotateLeft();
	void RotateRight();
	MainCharactor(Scene* scene);
	Sprite* Clone(Sprite* sprite);
	~MainCharactor();

	void UpdateVelocity(Point velocity);
};

