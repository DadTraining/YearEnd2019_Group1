#pragma once
#include "Objject.h"
#include "FightHammer.h"
#include "ui/CocosGUI.h"

enum Actions
{
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

	Scene *scene;
	Layer *layer;
	Animate *animate_push;
	Animate *animate_stun;

	Action *action_fight;
	Action *action_wait;
	Action *action_run;
	cocos2d::PhysicsBody* physicbody;

	FightHammer* f;
public:
	void setState(bool fight, bool moveLeft, bool moveRight, bool jump, bool stun, bool push);
	void Init();
	void InitialState();
	void CreateSprite();
	void InitialAction();

	void Update(float deltaTime);
	void Push();
	void Fight();
	void Wait();
	void Run();
	void Stun();
	void MoveLeft();
	void MoveRight();
	void Jump();
	

	void RotateLeft();
	void RotateRight();
	MainCharactor(Layer *layer);
	Sprite *Clone(Sprite *sprite);
	~MainCharactor();

	void UpdateVelocity(Point velocity);
};
