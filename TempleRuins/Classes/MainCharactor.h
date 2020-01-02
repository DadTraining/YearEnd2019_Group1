#pragma once
#include "Objject.h"
#include "FightHammer.h"
#include "ui/CocosGUI.h"

#define SCALE_SPRITE 0.12
#define SPEED_FRAME 0.2f
#define SPEED_FIGHT 0.2f
#define SPEED_RUN 10
#define SPEED_ROTATE 0.01f
#define BLOOD 100

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
	int numDiamond;
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

	Scene *scene;
	Layer *layer;
	Animate *animate_push;
	Animate *animate_stun;

	Action *action_fight;
	Action *action_wait;
	Action *action_run;

	FightHammer* f;
public:
	void setState(bool fight, bool moveLeft, bool moveRight, bool jump, bool stun, bool push, bool moveUp, bool moveDown);
	void Init();
	void InitialState();
	void CreateSprite();
	void InitialAction();
	void setDiamond(int diamon);
	int getDiamond();

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
	MainCharactor(Layer *layer);
	Sprite *Clone(Sprite *sprite);
	~MainCharactor();

	void UpdateVelocity(Point velocity);
};
