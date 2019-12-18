#pragma once

#include "Objject.h"
#include "Item_game.h"

#define NUM_ITEM 10
#define TIME_REMAIN 30
using namespace cocos2d;
class MiniGame : public Scene
{
private:
	vector<Objject* > items;
	CCPoint touch;
	int collect;
	Label* label_Collect;
public:
	static Scene* createMiniGame();
	virtual bool init();
	bool onTouchBegan(Touch* touch, Event* event);
	bool onTouchEnded(Touch* touch, Event* event);
	bool onTouchMoved(Touch* touch, Event* event);
	MiniGame();
	~MiniGame();

	
	bool OnTouhBegan(Touch* touch, Event* event);
	void update(float deltaTime);
	CREATE_FUNC(MiniGame);
};

