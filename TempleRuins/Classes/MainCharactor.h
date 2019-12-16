#pragma once
#include "Objject.h"

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
	MainCharactor(Scene* scene);
	~MainCharactor();
};

