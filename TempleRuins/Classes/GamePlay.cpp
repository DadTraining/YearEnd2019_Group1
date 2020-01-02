
#include "GamePlay.h"
#include "cocos2d.h"

Scene *GamePlay::createGame()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = GamePlay::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GamePlay::init()
{
	CreateMap();

	// initial physics for map
	InitialPhysics();

	// initial state
	InitialState();

	// initial object
	InitialObject();

	// add dispatcher
	AddDispatcher();

	// add button
	InitialButton();

	// add diamond
	//AddDiamond();

	// update
	scheduleUpdate();
	return true;
}
void GamePlay::CreateMap()
{
		auto layer_1 = Layer::create();
		_tileMap = new CCTMXTiledMap();
		_tileMap->initWithTMXFile("map.tmx");

		_background = _tileMap->layerNamed("Background");
		_wall = _tileMap->layerNamed("MapLv1");

		this->addChild(_tileMap);
}

void GamePlay::InitialState()
{
	// initial state
	fight = false;

	// initial direction
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	jump = false;
}

void GamePlay::InitialObject()
{
	// initial main charactor
	this->main_charactor = new MainCharactor(this);
	this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());

	CreateBloodBar();

	// initial spider
	this->spider = new Spider(this);
	this->setViewPointCenter(this->spider->GetSprite()->getPosition());

	// initial rock
	this->rock = new Rock(this);
}

void GamePlay::AddDispatcher()
{
	// key board
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GamePlay::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GamePlay::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	// listener contact
	auto contacListener = EventListenerPhysicsContact::create();
	contacListener->onContactBegin = CC_CALLBACK_1(GamePlay::OnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contacListener, this);

	//touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GamePlay::InitialButton()
{

	Director::getInstance()->getVisibleSize();
	//move Left
	mMoveLeftController = Sprite::create("touch_controller_normal.png");
	mMoveLeftController->setAnchorPoint(Vec2(0, 0));
	mMoveLeftController->setPosition(Vec2(50, 50));
	addChild(mMoveLeftController);

	mMoveLeftControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveLeftControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveLeftControllerPressed->setPosition(mMoveLeftController->getPosition());
	mMoveLeftControllerPressed->setVisible(false);
	addChild(mMoveLeftControllerPressed);

	//move Right
	mMoveRightController = Sprite::create("touch_controller_normal.png");
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setAnchorPoint(Vec2(0, 0));
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width + 50, 0));
	addChild(mMoveRightController);

	mMoveRightControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveRightControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveRightControllerPressed->setFlippedX(true);
	mMoveRightControllerPressed->setPosition(mMoveRightController->getPosition());
	mMoveRightControllerPressed->setVisible(false);
	addChild(mMoveRightControllerPressed);	
	//Button fight

	mBump = ui::Button::create("Button/hammer_normal.png","Button/hammer_pressed.png");
	mBump->setScale(0.3);
	mBump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 150, 100));
	mBump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fight, this));
	addChild(mBump);


	//move Up
	mMoveUpController = Sprite::create("touch_controller_normal.png");
	mMoveUpController->setFlippedY(true);
	mMoveUpController->setAnchorPoint(Vec2(0, 0));
	mMoveUpController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width + 50, 0)/2 + Vec2(0, mMoveLeftController->getContentSize().height));
	addChild(mMoveUpController);

	mMoveUpControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveUpControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveUpControllerPressed->setPosition(mMoveUpController->getPosition());
	mMoveUpControllerPressed->setVisible(false);
	addChild(mMoveUpControllerPressed);

	//move Down
	mMoveDownController = Sprite::create("touch_controller_normal.png");
	mMoveDownController->setAnchorPoint(Vec2(0, 0));
	mMoveDownController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width + 50, 0) / 2 - Vec2(0, mMoveLeftController->getContentSize().height));
	addChild(mMoveDownController);

	mMoveDownControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveDownControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveDownControllerPressed->setPosition(mMoveDownController->getPosition());
	mMoveDownControllerPressed->setVisible(false);
	addChild(mMoveDownControllerPressed);
}

void GamePlay::InitialPhysics()
{
	// ground
	Size layerSize = _wall->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _wall->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physic = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				physic->setMass(100);
				tileSet->setPhysicsBody(physic);
			}
		}
	}
}

bool GamePlay::OnContactBegin(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if (nodeA && nodeB) {
		if (nodeA->getTag() == 10 && nodeB->getTag() == 20) {
			if (!fight) { 
				this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION); 
				((MainCharactor*)(main_charactor))->Stun();
			}
			else if (CheckFight()) log("danh1");
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 10) {
			if (!fight) {
				this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION); 
				((MainCharactor*)(main_charactor))->Stun();
			}
			else if (CheckFight()) log("danh2");

		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 30)
		{
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 30 && nodeB->getTag() == 20)
		{
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 50)
		{
			((MainCharactor*)(main_charactor))->Push();
		}
		else if (nodeA->getTag() == 50 && nodeB->getTag() == 20)
		{
			((MainCharactor*)(main_charactor))->Push();
		}
	}

	return true;
}

bool GamePlay::CheckPush()
{
	return true;
}

bool GamePlay::CheckFight()
{
	float ySpider = this->spider->GetSprite()->getPosition().y;
	float yCharac = this->main_charactor->GetSprite()->getPosition().y;
	float ySpiderSize = this->spider->GetSprite()->getContentSize().height;
	float yCharacSize = this->main_charactor->GetSprite()->getContentSize().height;

	/*if (fight && (yCharac > ySpider - (ySpiderSize / 2) && yCharac < ySpider + (ySpiderSize / 2))) {
	return true;
}*/
	if (fight)
		return true;

	return false;
}

void GamePlay::CreateBloodBar()
	{
		Layer *layer_1 = Layer::create();
		auto bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
		bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
		bloodBar_1->setPercent(100);
		bloodBar_1->setPosition(Vec2(this->main_charactor->getVisibleSize().width / 2, this->main_charactor->getVisibleSize().height - 30));

		auto bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
		bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
		bloodBar_2->setPercent(this->main_charactor->GetBlood());
		bloodBar_2->setPosition(bloodBar_1->getPosition());

		this->addChild(bloodBar_1);
		this->addChild(bloodBar_2);
	}

void GamePlay::Fight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		fight = true;
		break;
	case ui::Widget::TouchEventType::ENDED:
		fight = false;
		break;
}
}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_Q:
		{
			if (moveLeft || moveRight)
			{
				fight = false;
			}
			else
			{
				fight = true;
			}

			break;
		}

		case EventKeyboard::KeyCode::KEY_A:
		{
			moveLeft = true;
			break;
		}
		case EventKeyboard::KeyCode::KEY_D:
		{
			moveRight = true;
			break;
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			moveUp = true;
			break;
		}
		case EventKeyboard::KeyCode::KEY_S:
		{
			moveDown = true;
			break;
		}
		default:
			break;
		}
	}	

void GamePlay::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
	{
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_Q:
		{
			fight = false;
			break;
		}

		case EventKeyboard::KeyCode::KEY_A:
		{
			moveLeft = false;
			break;
		}
		case EventKeyboard::KeyCode::KEY_D:
		{
			moveRight = false;
			break;
		}
		case EventKeyboard::KeyCode::KEY_W:
		{
			moveUp = false;
			break;
		}
		case EventKeyboard::KeyCode::KEY_S:
		{
			moveDown = false;
			break;
		}
		default:
			break;
		}
	}

void GamePlay::update(float deltaTime)

{
	// update main charactor
	main_charactor->Update(deltaTime);
	((MainCharactor*)main_charactor)->setState(fight, moveLeft, moveRight, jump, stun, push, moveUp, moveDown);

	// update spider
	spider->Update(deltaTime);
	UpdateController();


		// update spider
		//spider->Update(deltaTime);

		this->setViewPointCenter(main_charactor->GetSprite()->getPosition());
	}	

void GamePlay::setViewPointCenter(CCPoint position)
	{
		CCPoint p = _tileMap->getPosition();
		//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSize winSize = Director::getInstance()->getVisibleSize();
		CCPoint viewPoint = ccp(0, 0);
		/*int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	_tileMap->setPosition(viewPoint);*/
		Vec2 mapMoveDistance = Vec2(0, 0);
		Vec2 mcMoveDistance = Vec2(0, 0);
		if (moveRight)
		{
			if (main_charactor->GetSprite()->getPosition().x < winSize.width / 2)
			{
				mcMoveDistance = Vec2(5, 0);
			}
			else
			{
				float mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width;
				if (_tileMap->getPosition().x > -(mapWidth - winSize.width - 5))
				{
					mapMoveDistance = -Vec2(5, 0);
				}
				else if (main_charactor->GetSprite()->getPosition().x <= (winSize.width - 5 - main_charactor->GetSprite()->getContentSize().width / 2))
				{
					mcMoveDistance = Vec2(5, 0);
				}
			}
		}
		else if (moveLeft)
		{
			if (main_charactor->GetSprite()->getPosition().x > winSize.width / 2)
			{
				mcMoveDistance = -Vec2(5, 0);
			}
			else
			{
				if (_tileMap->getPosition().x <= -5)
				{
					mapMoveDistance = Vec2(5, 0);
				}
				else if (main_charactor->GetSprite()->getPosition().x >= 5 + main_charactor->GetSprite()->getContentSize().width / 2)
				{
					mcMoveDistance = -Vec2(5, 0);
				}
			}
		}
		else if (moveUp)
		{
			if (main_charactor->GetSprite()->getPosition().y < winSize.height / 2)
			{
				mcMoveDistance = Vec2(0, 5);
			}
			else
			{
				float mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
				if (_tileMap->getPosition().y > -(mapHeight - winSize.height - 5))
				{
					mapMoveDistance = -Vec2(0, 5);
				}
				else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height - 5 - main_charactor->GetSprite()->getContentSize().height / 2))
				{
					mcMoveDistance = Vec2(0, 5);
				}
			}
		}
		else if (moveDown)
		{
			if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
			{
				mcMoveDistance = -Vec2(0, 5);
			}
			else
			{
				if (_tileMap->getPosition().y <= -5)
				{
					mapMoveDistance = Vec2(0, 5);
				}
				else if (main_charactor->GetSprite()->getPosition().y >= 5 + main_charactor->GetSprite()->getContentSize().height / 2)
				{
					mcMoveDistance = -Vec2(0, 5);
				}
			}
		}

		if (mcMoveDistance != Vec2(0, 0))
		{
			main_charactor->GetSprite()->setPosition(main_charactor->GetSprite()->getPosition() + mcMoveDistance);
		}

		if (mapMoveDistance != Vec2(0, 0))
		{
			_tileMap->setPosition(_tileMap->getPosition() + mapMoveDistance);

			spider->GetSprite()->setPosition(spider->GetSprite()->getPosition() + mapMoveDistance);

			rock->GetSprite()->setPosition(rock->GetSprite()->getPosition() + mapMoveDistance);
		}

		/*_tileMap->setPosition(_tileMap->getPosition() + viewPoint);
	diamond->GetSprite()->setPosition(diamond->GetSprite()->getPosition() + ccpSub(viewPoint, p));
	spider->GetSprite()->setPosition(spider->GetSprite()->getPosition() + ccpSub(viewPoint, p));

	rock->GetSprite()->setPosition(rock->GetSprite()->getPosition() + ccpSub(viewPoint, p));*/
	}	

GamePlay::GamePlay()
{
}		

GamePlay::~GamePlay()
{

}

bool GamePlay::onTouchBegan(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	return true;
}

void GamePlay::onTouchMoved(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
	mCurrentTouchPoint = touch->getLocation();
	log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
}

void GamePlay::onTouchEnded(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
}

void GamePlay::UpdateController()
{
	//cheat key
	if (mCurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW) //move left
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(1, 1);
	}
	if (mCurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) //move right		
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(66, 1);
	}
	if (mCurrentKey == EventKeyboard::KeyCode::KEY_UP_ARROW) //jump
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(130, 1);
	}

	if (mCurrentKey == EventKeyboard::KeyCode::KEY_SPACE) //jump
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(194, 1);
	}

	switch (mCurrentTouchState)
	{
	case ui::Widget::TouchEventType::BEGAN:
	case ui::Widget::TouchEventType::MOVED:

		if (Rect(mMoveLeftController->getPosition().x, mMoveLeftController->getPosition().y, mMoveLeftController->getContentSize().width, mMoveLeftController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW) //move left
		{
			EnablePressedControlLeftRight(true, true);
			moveLeft = true;
			moveRight = false;
			moveUp = false;
			moveDown = false;
		}
		else
		{
			EnablePressedControlLeftRight(true, false);
		}

		if (Rect(mMoveRightController->getPosition().x, mMoveRightController->getPosition().y, mMoveRightController->getContentSize().width, mMoveRightController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) //move right		
		{
			EnablePressedControlLeftRight(false, true);
			moveLeft = false;
			moveRight = true;
			moveUp = false;
			moveDown = false;
		}
		else
		{
			EnablePressedControlLeftRight(false, false);
		}

		if (Rect(mMoveUpController->getPosition().x, mMoveUpController->getPosition().y, mMoveUpController->getContentSize().width, mMoveUpController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_UP_ARROW) //move up		
		{
			EnablePressedControlUpDown(true, true);
			moveLeft = false;
			moveRight = false;
			moveUp = true;
			moveDown = false;
		}
		else
		{
			EnablePressedControlUpDown(true, false);
		}

		if (Rect(mMoveDownController->getPosition().x, mMoveDownController->getPosition().y, mMoveDownController->getContentSize().width, mMoveDownController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_DOWN_ARROW) //move down		
		{
			EnablePressedControlUpDown(false, true);
			moveLeft = false;
			moveRight = false;
			moveUp = false;
			moveDown = true;
		}
		else
		{
			EnablePressedControlUpDown(false, false);
		}

		break;
	case ui::Widget::TouchEventType::ENDED:
		EnablePressedControlLeftRight(true, false);
		EnablePressedControlLeftRight(false, false);
		EnablePressedControlUpDown(true, false);
		EnablePressedControlUpDown(false, false);
		moveLeft = false;
		moveRight = false;
		moveUp = false;
		moveDown = false;
		((MainCharactor*)main_charactor)->setState(fight, moveLeft, moveRight, jump, stun, push, moveUp, moveDown);
		break;
	}

}

void GamePlay::EnablePressedControlLeftRight(bool isLeft, bool pressed) 
{
	if (isLeft) {
		mMoveLeftController->setVisible(!pressed);
		mMoveLeftControllerPressed->setVisible(pressed);
	}
	else {
		mMoveRightController->setVisible(!pressed);
		mMoveRightControllerPressed->setVisible(pressed);
	}
	
}

void GamePlay::EnablePressedControlUpDown(bool isUp, bool pressed)
{
	if (isUp) {
		mMoveUpController->setVisible(!pressed);
		mMoveUpControllerPressed->setVisible(pressed);
	}
	else {
		mMoveDownController->setVisible(!pressed);
		mMoveDownControllerPressed->setVisible(pressed);
	}

}
