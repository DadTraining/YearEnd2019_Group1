
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

	// update
	scheduleUpdate();

	return true;
}

void GamePlay::CreateMap()
{
	auto layer_1 = Layer::create();
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map2.tmx");
	_tileMap->setScale(2);
	_background = _tileMap->layerNamed("Background");
	_wall = _tileMap->layerNamed("MapLv2");
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
	fall = false;
}

void GamePlay::InitialObject()
{
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asInt();
		log("%f",posX);
		int posY = properties.at("y").asInt();
		log("%f", posY);
		int type = object.asValueMap().at("type").asInt();

		if (type == 1)
		{
			this->main_charactor = new MainCharactor(this);
			this->main_charactor->GetSprite()->setPosition(Vec2(posX, posY));
			log("%f----------%f",posX,posY);
			log("%f_______%f", this->main_charactor->GetSprite()->getPosition().x, this->main_charactor->GetSprite()->getPosition().y);
			this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
			CreateBloodBar();
			CreateNumDiamon();
		}
		/*else if (type == 2)
		{
			Spider *spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX, posY));
			spider->setCatogory(true);
			spiders.push_back(spider);
		}*/
		/*else if (type == 3)
		{
			Spider* spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX, posY));
			spider->setCatogory(false);
			spiders.push_back(spider);
		}*/
		/*else if (type == 4) {
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
		}*/
	}
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

	// touch
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
				physic->setTag(TAG_MAP);
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
		// charactor vs spider
		if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_CHARACTOR)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
			((MainCharactor *)(main_charactor))->Stun();
		}
		else if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_SPIDER)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - BLOOD_REDUCTION);
			((MainCharactor *)(main_charactor))->Stun();
		}

		// main charactor vs diamond
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_DIAMOND)
		{
			numDiamond++;
			nodeB->removeFromParentAndCleanup(true);
			//nodeB->setPosition(Vec2(-200, -200));
		}
		else if (nodeA->getTag() == TAG_DIAMOND && nodeB->getTag() == TAG_CHARACTOR)
		{
			numDiamond++;
			nodeA->removeFromParentAndCleanup(true);
			//nodeA->setPosition(Vec2(-200, -200));
		}

		// main charactor vs glass
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_GLASS) {
			//nodeB->removeFromParentAndCleanup(true);
			nodeB->setPosition(Vec2(-100, -100));
		}
		else if (nodeA->getTag() == TAG_GLASS && nodeB->getTag() == TAG_CHARACTOR) {
			//nodeA->removeFromParentAndCleanup(true);
			nodeA->setPosition(Vec2(-100, -100));
		}

		// fight
		if (nodeA->getTag() == TAG_FIGHT && nodeB->getTag() == TAG_ROCK) {
			log("fight1");
		}
		else if (nodeA->getTag() == TAG_ROCK && nodeB->getTag() == TAG_FIGHT) {
			log("fight2");
		}
	}

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
	CCString *num = CCString::createWithFormat("%i/50", numDiamond);
	LabelNumDiamon = Label::createWithTTF(num->getCString(), "fonts/Marker Felt.ttf", 30);
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50, 0));
	this->addChild(LabelNumDiamon, 2);
}

void GamePlay::Fight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		//fight = true;
		break;
	case ui::Widget::TouchEventType::ENDED:
		//fight = false;
		break;
	}
}

void GamePlay::push_rock()
{
	push = false;
	int index = -1;
	index = check_push();
	if (index != -1) {
		push = true;

		Sprite* _rock = rocks.at(index)->GetSprite();

		if (_rock->getPosition().x > main_charactor->GetSprite()->getPosition().x) {
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() +
				Vec2(SPEED_CHARACTOR_RUN, 0));
		}
		else {
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() -
				Vec2(SPEED_CHARACTOR_RUN, 0));
		}

		((MainCharactor*)(main_charactor))->Push();
	}
}

int GamePlay::check_push()
{
	int index = 0;
	Vec2 p_main = main_charactor->GetSprite()->getPosition();
	Vec2 p_rock = rocks.at(0)->GetSprite()->getPosition();
	float min_horizontal = distance(p_main.x, p_rock.x);

	float _dis_horizontal = main_charactor->getSize().width / 2 + rocks.at(0)->getSize().width / 2;
	float _dis_vertical = main_charactor->getSize().height / 2 + rocks.at(0)->getSize().height / 2;

	float min_vertical = distance(p_main.y, rocks.at(index)->GetSprite()->getPosition().y);

	if (min_horizontal <= _dis_horizontal && min_vertical < _dis_vertical) {
		return index;
	}

	return -1;
}

float GamePlay::distance(float main, float rock)
{
	//Vec2 P_main = main->GetSprite()->getPosition();
	//Vec2 P_rock = rock->GetSprite()->getPosition();

	//float dis = sqrt((P_main.x - P_rock.x)*(P_main.x - P_rock.x) + (P_main.y - P_rock.y)*(P_main.y - P_rock.y));
	float dis = abs(main - rock);

	return dis;
}

void GamePlay::Jump(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		log("began");
		//jump = true;
		fall = false;
		moveUp = true;
		break;
	case ui::Widget::TouchEventType::ENDED:
		log("ended");
		//jump = false;
		fall = true;
		moveUp = false;
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
	CCString *num = CCString::createWithFormat("%i/50", numDiamond);
	LabelNumDiamon->setString(num->getCString());

	// push rock
	push_rock();
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
			mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		else
		{
			float mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width;
			if (_tileMap->getPosition().x > -(mapWidth - winSize.width - SPEED_CHARACTOR_RUN))
			{
				mapMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
			}
			else if (main_charactor->GetSprite()->getPosition().x <= (winSize.width - SPEED_CHARACTOR_RUN))
			{
				mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
			}
		}
	}
	else if (moveLeft)
	{
		if (main_charactor->GetSprite()->getPosition().x > winSize.width / 2)
		{
			mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		else
		{
			if (_tileMap->getPosition().x <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
			}
			else if (main_charactor->GetSprite()->getPosition().x >= SPEED_CHARACTOR_RUN)
			{
				mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
			}
		}
	}
	else if (moveUp || jump)
	{

		if (main_charactor->GetSprite()->getPosition().y < winSize.height / 2)
		{
			mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
				float mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
			if (_tileMap->getPosition().y > -(mapHeight - winSize.height - SPEED_CHARACTOR_RUN))
				{
					mapMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
				}
				else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height))
				{
					mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
				}
		}
	}
	else if (moveDown)
	{
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
			}
			else if (main_charactor->GetSprite()->getPosition().y >= SPEED_CHARACTOR_RUN)
			{
				mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
	}

	if (main_charactor->GetSprite()->getPosition().y < Director::getInstance()->getWinSize().height / 2 &&
		_tileMap->getPosition().y < 0) {
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			//mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN-3);
			}
			else if (main_charactor->GetSprite()->getPosition().y >= SPEED_CHARACTOR_RUN)
			{
				//mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
		if (moveLeft) {
			mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		if (moveRight) {
			mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
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
	//log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
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
			moveUp = false;
			moveDown = false;
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
			moveUp = false;
			moveDown = false;
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
