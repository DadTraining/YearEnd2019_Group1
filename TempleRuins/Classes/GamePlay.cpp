
#include "GamePlay.h"
#include "cocos2d.h"

Scene *GamePlay::createGame()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setSubsteps(8);
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
	_phy = _tileMap->layerNamed("physics");
	_phy->setVisible(false);
	mObjectGroup = _tileMap->getObjectGroup("Objects");

	this->addChild(_tileMap);
}

void GamePlay::InitialState()
{
	// initial number diamon
	this->numDiamond = 0;

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
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asInt();
		int posY = properties.at("y").asInt();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1)
		{
			this->main_charactor = new MainCharactor(this);
			this->main_charactor->GetSprite()->setPosition(Vec2(posX, posY));
			this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
			CreateBloodBar();
			CreateNumDiamon();
		}
		else if (type == 2)
		{
			Spider *spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX, posY));
			spider->setCatogory(true);
			spiders.push_back(spider);
		}
		/*else if (type == 3)
		{
			Spider* spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX, posY));
			spider->setCatogory(false);
			spiders.push_back(spider);
		}*/
		else if (type == 4) {
			Objject* glass = new Glass(this);
			glass->GetSprite()->setPosition(Vec2(posX, posY));
			glasss.push_back(glass);
		}
		else if (type == 5) {
			Objject* diamon = new Diamond(this);
			diamon->GetSprite()->setPosition(Vec2(posX, posY));
			diamons.push_back(diamon);
		}
		else if (type == 6) {
			Objject* rock = new Rock(this);
			rock->GetSprite()->setPosition(Vec2(posX, posY));
			rocks.push_back(rock);
		}
	}
}

void GamePlay::AddDispatcher()
{
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
	mMoveLeftController->setOpacity(0);
	addChild(mMoveLeftController);

	mMoveLeftControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveLeftControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveLeftControllerPressed->setPosition(mMoveLeftController->getPosition());
	mMoveLeftControllerPressed->setVisible(false);
	mMoveLeftControllerPressed->setOpacity(50);
	addChild(mMoveLeftControllerPressed);

	//move Right
	mMoveRightController = Sprite::create("touch_controller_normal.png");
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setAnchorPoint(Vec2(0, 0));
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width, 0));
	mMoveRightController->setOpacity(0);
	addChild(mMoveRightController);

	mMoveRightControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveRightControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveRightControllerPressed->setFlippedX(true);
	mMoveRightControllerPressed->setPosition(mMoveRightController->getPosition());
	mMoveRightControllerPressed->setOpacity(50);
	mMoveRightControllerPressed->setVisible(false);
	addChild(mMoveRightControllerPressed);
	
	//Button fight
	mBump = ui::Button::create("Button/hammer_normal.png", "Button/hammer_pressed.png");
	mBump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 150, 100));
	mBump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fight, this));
	mBump->setOpacity(50);
	addChild(mBump);

	//Button Jump
	mJump = ui::Button::create("Button/hammer_normal.png", "Button/hammer_pressed.png");
	mJump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 80, 150));
	mJump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Jump, this));
	mJump->setOpacity(50);
	addChild(mJump);





}

void GamePlay::InitialPhysics()
{
	//world
	/*auto edgeBody = PhysicsBody::createEdgeBox(this->main_charactor->getVisibleSize() + Size(0, 200), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(100);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(this->main_charactor->getVisibleSize().width / 2, this->main_charactor->getVisibleSize().height / 2 - 100);
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);*/

	// ground
	Size layerSize = _phy->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _phy->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physic = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				physic->setMass(100);
				physic->setTag(70);
				tileSet->setPhysicsBody(physic);
			}
		}
	}
}

bool GamePlay::OnContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10 && nodeB->getTag() == 20)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
			((MainCharactor *)(main_charactor))->Stun();
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 10)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
			((MainCharactor *)(main_charactor))->Stun();
		}

		// main charactor vs diamond
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 30)
		{
			numDiamond++;
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 30 && nodeB->getTag() == 20)
		{
			numDiamond++;
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 20 && nodeB->getTag() == 50)
		{
			((MainCharactor *)(main_charactor))->Push();
		}
		else if (nodeA->getTag() == 50 && nodeB->getTag() == 20)
		{
			((MainCharactor *)(main_charactor))->Push();
		}

		// main charactor vs glass
		if (nodeA->getTag() == 20 && nodeB->getTag() == 80) {
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == 80 && nodeB->getTag() == 20) {
			nodeA->removeFromParentAndCleanup(true);
		}

		//if (nodeA->getTag() == 10 && nodeB->getTag() == 70 || nodeA->getTag() == 70 && nodeB->getTag() == 10) {
		//	// dao nguoc di chuyen con nhen

		//}

		// fight
		/*else if (nodeA->getTag() == 60 && nodeB->getTag() == 10) {
			this->spider->SetBlood(this->spider->GetBlood() - 1);
		}
		else if (nodeA->getTag() == 10 && nodeB->getTag() == 60) {
			this->spider->SetBlood(this->spider->GetBlood() - 1);
		}*/
	}

	return true;
}

bool GamePlay::CheckPush()
{
	return true;
}

void GamePlay::CreateBloodBar()
{
	Layer *layer_1 = Layer::create();
	auto bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_1->setPercent(100);
	bloodBar_1->setPosition(Vec2(150, this->main_charactor->getVisibleSize().height - 30));

	bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
	bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
	bloodBar_2->setPercent(this->main_charactor->GetBlood());
	bloodBar_2->setPosition(bloodBar_1->getPosition());

	this->addChild(bloodBar_1);
	this->addChild(bloodBar_2);
}

void GamePlay::CreateNumDiamon()
{
	// sprite diamon
	auto NumDiamon = ResourceManager::GetInstance()->GetSpriteById(5);
	NumDiamon->setScale(0.4);
	NumDiamon->setPosition(bloodBar_2->getPosition() + Vec2(200, 0));
	this->addChild(NumDiamon, 2);

	// label number
	CCString *num = CCString::createWithFormat("%i", numDiamond);
	LabelNumDiamon = Label::createWithTTF(num->getCString(), "fonts/Marker Felt.ttf", 30);
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50, 0));
	this->addChild(LabelNumDiamon, 2);
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

void GamePlay::Jump(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		log("began");
		jump = true;
		break;
	case ui::Widget::TouchEventType::ENDED:
		log("ended");
		jump = false;
		break;
	}
}

void GamePlay::update(float deltaTime)
{
		// update main charactor
		main_charactor->Update(deltaTime);
		((MainCharactor *)main_charactor)->setState(fight, moveLeft, moveRight, jump, stun, push);

		UpdateController();

		// set view
		this->setViewPointCenter(main_charactor->GetSprite()->getPosition());

	// update blood
	bloodBar_2->setPercent(this->main_charactor->GetBlood());

	// update number diamond
	CCString *num = CCString::createWithFormat("%i", numDiamond);
	LabelNumDiamon->setString(num->getCString());
}	

void GamePlay::setViewPointCenter(CCPoint position)
	{
		CCSize winSize = Director::getInstance()->getVisibleSize();

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
				else if (main_charactor->GetSprite()->getPosition().x <= (winSize.width - 5))
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
				else if (main_charactor->GetSprite()->getPosition().x >= 5)
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
				else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height))
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
				else if (main_charactor->GetSprite()->getPosition().y >= 5)
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

			/*if(((Spider*)(spider))->isAlive())
			spider->GetSprite()->setPosition(spider->GetSprite()->getPosition() + mapMoveDistance);

			rock->GetSprite()->setPosition(rock->GetSprite()->getPosition() + mapMoveDistance);*/

			// update spider
			for (int i = 0; i < spiders.size(); i++)
			{
				spiders.at(i)->GetSprite()->setPosition(spiders.at(i)->GetSprite()->getPosition() + mapMoveDistance);
			}

			// update glass
			for (int i = 0; i < glasss.size(); i++)
			{
				glasss.at(i)->GetSprite()->setPosition(glasss.at(i)->GetSprite()->getPosition() + mapMoveDistance);
			}

			// update diamon
			for (int i = 0; i < diamons.size(); i++)
			{
				diamons.at(i)->GetSprite()->setPosition(diamons.at(i)->GetSprite()->getPosition() + mapMoveDistance);
			}

			// update rock
			for (int i = 0; i < rocks.size(); i++)
			{
				rocks.at(i)->GetSprite()->setPosition(rocks.at(i)->GetSprite()->getPosition() + mapMoveDistance);
			}
		}
	}	

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

bool GamePlay::onTouchBegan(Touch * touch, Event * event)
	{
		mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
		mCurrentTouchPoint = touch->getLocation();
		return true;
	}		

void GamePlay::onTouchMoved(Touch * touch, Event * event)
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = touch->getLocation();
		log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
	}	

void GamePlay::onTouchEnded(Touch * touch, Event * event)
	{
		mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
		mCurrentTouchPoint = Point(-1, -1);
	}	

void GamePlay::UpdateController()
	{
		switch (mCurrentTouchState)
		{
		case ui::Widget::TouchEventType::BEGAN:
		case ui::Widget::TouchEventType::MOVED:

			if (Rect(mMoveLeftController->getPosition().x, mMoveLeftController->getPosition().y, mMoveLeftController->getContentSize().width, mMoveLeftController->getContentSize().height).containsPoint(mCurrentTouchPoint) || mCurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW) //move left
			{
				EnablePressedControlLeftRight(true, true);
				moveLeft = true;
				moveRight = false;
			}
			else
			{
				EnablePressedControlLeftRight(true, false);
			}

			if (Rect(mMoveRightController->getPosition().x, mMoveRightController->getPosition().y, mMoveRightController->getContentSize().width, mMoveRightController->getContentSize().height).containsPoint(mCurrentTouchPoint) || mCurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) //move right
			{
				EnablePressedControlLeftRight(false, true);
				moveLeft = false;
				moveRight = true;
			}
			else
			{
				EnablePressedControlLeftRight(false, false);
			}
			break;

		case ui::Widget::TouchEventType::ENDED:
			EnablePressedControlLeftRight(true, false);
			EnablePressedControlLeftRight(false, false);
			moveLeft = false;
			moveRight = false;
			((MainCharactor *)main_charactor)->setState(fight, moveLeft, moveRight, jump, stun, push);
			break;
		}
	}

void GamePlay::EnablePressedControlLeftRight(bool isLeft, bool pressed)
{
	if (isLeft)
	{
		mMoveLeftController->setVisible(!pressed);
		mMoveLeftControllerPressed->setVisible(pressed);
	}
	else
	{
		mMoveRightController->setVisible(!pressed);
		mMoveRightControllerPressed->setVisible(pressed);
	}
}
