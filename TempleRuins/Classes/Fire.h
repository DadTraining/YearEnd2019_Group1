#pragma once
#include "Objject.h"

USING_NS_CC;
class Fire : public Objject
{
private:
	Layer* layer;
	std::vector<Vec2> Fire_pos;
	CCTMXTiledMap *_tileMap;
	bool AI = false;
	Vec2 pos_main;
	PhysicsBody* physic;
public:
	void Init();
	void Update(float deltaTime);
	Fire(Layer* layer);
	Size getSize();
	void setPos(vector<Vec2> Fire_pos, CCTMXTiledMap *_tileMap);
	void setPosMain(Vec2 pos_main);
	void setAI(bool c);
	bool isAI();
	void runAI();
	float distance(Vec2 main, Vec2 AI);
	~Fire();
};

