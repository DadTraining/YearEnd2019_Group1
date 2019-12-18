#pragma once
#include "Objject.h"

#define SCALE_SPRITE 0.3
#define SPEED_FRAME 0.2f

enum Actions_Charactor {
	C_UP,
	C_DOWN,
	C_LEFT,
	C_RIGHT,
	C_PUSH,
	C_FIGHT,
	C_WAIT
};

class MainCharactor : public Objject
{
private:
	Actions_Charactor action;
	Scene* scene;
	Animate* animate_push;
	Animate* animate_up;
	Animate* animate_down;
	Animate* animate_left;
	Animate* animate_right;
	Animate* animate_fight;
	Animate* animate_wait;
	Animate* animate_run;
public:
	void Init();
	void Update(float deltaTime);
	void Up();
	void Down();
	void Left();
	void Right();
	void Push();
	void Fight();
	void Wait();
	void Run();
	MainCharactor(Scene* scene);
	Sprite* Clone(Sprite* sprite);
	~MainCharactor();
};

