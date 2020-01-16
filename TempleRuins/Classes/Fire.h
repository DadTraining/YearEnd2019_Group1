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
	Vec2 AI_View;
	Vec2 AI_pos;
public:
	void Init();
	void Update(float deltaTime);
	Fire(Layer* layer);
	Size getSize();
	void setPos(vector<Vec2> Fire_pos, CCTMXTiledMap *_tileMap, Vec2 AI_View);
	void setPosMain(Vec2 pos_main);
	void setAI(bool c);
	bool isAI();
	void runAI();
	Vec2 getMove(Vec2 head);
	float distance(Vec2 main, Vec2 AI);
	~Fire();
};