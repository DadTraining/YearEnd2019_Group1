#ifndef __MINIGAME_SCENE_H__
#define __MINIGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MiniGame : public cocos2d::Layer
{
private:
	Sprite* diamond;
	PhysicsWorld* m_world;
	int score = 0;
	Label* scoreLabel;
	int life;
	Label* lifeLabel;
	CCParallaxNode *_backgroundNode;
	CCSprite *_spacedust1;
	CCSprite *_spacedust2;
	CCSprite *_planetsunrise;
	CCSprite *_galaxy;
	CCSprite *_spacialanomaly;
	CCSprite *_spacialanomaly2;
	Vector<Sprite*> meteors;
	Vector<Sprite*> diamonds;
public:
	void setScore(int score) { this->score = score; };

	void setPhyWorld(PhysicsWorld* world) { m_world = world; };

	static cocos2d::Scene* createScene();

	virtual bool init();

	bool onContactBegin(PhysicsContact &contact);

	bool onTouchBegan(Touch *touch, Event *event);

	virtual void update(float deltaTime);

	// implement the "static create()" method manually
	CREATE_FUNC(MiniGame);
};

#endif // __MINIGAME_SCENE_H__
