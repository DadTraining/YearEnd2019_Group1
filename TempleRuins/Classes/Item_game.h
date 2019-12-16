#pragma once
#include "Objject.h"
class Item_game : public Objject
{
private:
	Scene* scene;
	CCPoint touch;
public:
	void SetTouch(CCPoint touch);
	void Init();
	void Update(float deltaTime);
	Item_game(Scene* scene);
	~Item_game();
	Sprite* Clone(Sprite* sprite);
	void random(Objject* object);
};

