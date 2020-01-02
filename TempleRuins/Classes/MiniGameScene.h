#ifndef __MINIGAME_SCENE_H__
#define __MINIGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MiniGame : public cocos2d::Layer
{
public:

	PhysicsWorld* m_world;

	void setPhyWorld(PhysicsWorld* world) { m_world = world; };

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onAcceleration(Acceleration* acc, Event* unused_event);

	bool onContactBegin(PhysicsContact &contact);



	// implement the "static create()" method manually
	CREATE_FUNC(MiniGame);
};

#endif // __MINIGAME_SCENE_H__