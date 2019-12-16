#pragma once
#include "Objject.h"

#define SCALE_SPRITE 0.3

enum Actions {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	PUSH,
	WAIT
};

class MainCharactor : public Objject
{
private:
	Actions action;
	Scene* scene;
public:
	void Init();
	void Update(float deltaTime);
	void Up();
	void Down();
	void Left();
	void Right();
	void Push();
	MainCharactor(Scene* scene);
	Sprite* Clone(Sprite* sprite);
	~MainCharactor();
};

