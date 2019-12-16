#pragma once
#include "C:\Users\Admin\Desktop\2019\YearEnd2019_Group1\TempleRuins\cocos2d\cocos\2d\CCScene.h"
#include "Objject.h"
#include "Item_game.h"

#define NUM_ITEM 10
#define TIME_REMAIN 30

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
	MiniGame();
	~MiniGame();
	bool OnTouhBegan(Touch* touch, Event* event);
	void update(float deltaTime);
	CREATE_FUNC(MiniGame);
};

