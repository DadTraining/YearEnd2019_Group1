
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class LoadingLogo : public cocos2d::Scene
{
private:
    int timeRemain;
    Scene* scene;
    Label* label_Timer;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void Init();
    void Update(float deltaTime);
    Sprite* Clone(Sprite* sprite);
    CountTimer(Scene* scene, int timeRemain);
    ~CountTimer();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void changeLoading(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingLogo);
};

#endif // __HELLOWORLD_SCENE_H__
