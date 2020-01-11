#include "GamePlay.h"
#include "ControlMusic.h"

cocos2d::Sprite* mPauseLayer;
cocos2d::Sprite* mHeader;
cocos2d::ui::Button *mBump;
cocos2d::ui::Button *mJump;
cocos2d::ui::Button *btnPause;

float GamePlay::distance_1(float p_1, float p_2)
{
	return p_1 - p_2;
}

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
	//Create background music
	if (ControlMusic::GetInstance()->isMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/angkor_wat.mp3", true);
	}

	//Create Map
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

	//create pause layer
	createPauseLayer();

	// update
	scheduleUpdate();

	return true;
}

void GamePlay::CreateMap()
{
	auto layer_1 = Layer::create();
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map.tmx");
	//_tileMap->setScale(2);
	_background = _tileMap->layerNamed("Background");
	_wall = _tileMap->layerNamed("MapLv1");
	_phy = _tileMap->layerNamed("physics");
	_phy->setVisible(false);
	_thang = _tileMap->layerNamed("Thang");
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
		int posY = properties.at("y").asInt();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1)//Create Charactor
		{
			this->main_charactor = new MainCharactor(this);
			this->main_charactor->GetSprite()->setPosition(Vec2(posX, posY));
			this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
			CreateBloodBar();
			CreateNumDiamon();
		}
		else if (type == 2)//Create Spider
		{
			Spider *spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX, posY));
			spider->setCatogory(true);
			spiders.push_back(spider);
		}
		else if (type == 4) {//Create Glass
			Objject* glass = new Glass(this);
			glass->GetSprite()->setPosition(Vec2(posX, posY));
			glasss.push_back(glass);
		}
		else if (type == 5) {//Create Diamond
			Objject* diamon = new Diamond(this);
			diamon->GetSprite()->setPosition(Vec2(posX, posY));
			diamons.push_back(diamon);
		}
		else if (type == 6) {//Create Rock
			Objject* rock = new Rock(this);
			rock->GetSprite()->setPosition(Vec2(posX, posY));
			rocks.push_back(rock);
		}
		else if (type == 7) {
			_thang_1 = Vec2(posX, posY);
		}
		else if (type == 8) {
			_thang_2 = Vec2(posX, posY);
		}
		else if (type == 9) {
			_ground_Pos = Vec2(posX, posY);
		}
		else if (type == 10) {
			_ground_Pos_1 = Vec2(posX, posY);
		}
		else if (type == 11) {
			_ground_Pos_2 = Vec2(posX, posY);
		}
		else if (type == 12) {
			_ground_Pos_12 = Vec2(posX, posY);
		}
		else if (type == 13) {
			_ground_Pos_13 = Vec2(posX, posY);
		}
		else if (type == 14) {
			_ground_Pos_14 = Vec2(posX, posY);
		}
		else if (type == 15) {
			_ground_Pos_15 = Vec2(posX, posY);
		}
		else if (type == 16) {
			_ground_Pos_16 = Vec2(posX, posY);
		}
		else if (type == 17) {
			_ground_Pos_17 = Vec2(posX, posY);
		}
		else if (type == 18) {
			_ground_Pos_18 = Vec2(posX, posY);
		}
		else if (type == 19) {
			_ground_Pos_19 = Vec2(posX, posY);
		}
		else if (type == 20) {
			_ground_Pos_20 = Vec2(posX, posY);
		}
		else if (type == 21) {
			_ground_Pos_21 = Vec2(posX, posY);
		}
		else if (type == 22) {
			_ground_Pos_22 = Vec2(posX, posY);
		}
		else if (type == 23) {
			_ground_Pos_23 = Vec2(posX, posY);
		}
		else if (type == 24) {
			_ground_Pos_24 = Vec2(posX, posY);
		}
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
	mMoveLeftController->setScale(1.5);
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
	mMoveRightController->setScale(1.5);
	addChild(mMoveRightController);

	mMoveRightControllerPressed = Sprite::create("touch_controller_pressed.png");
	mMoveRightControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveRightControllerPressed->setFlippedX(true);
	mMoveRightControllerPressed->setPosition(mMoveRightController->getPosition());
	mMoveRightControllerPressed->setOpacity(50);
	mMoveRightControllerPressed->setVisible(false);
	addChild(mMoveRightControllerPressed);

	//Button Fight
	mBump = ui::Button::create("Button/hammer_normal.png", "Button/hammer_pressed.png");
	mBump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 180, 100));
	mBump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fight, this));
	mBump->setOpacity(50);
	addChild(mBump);

	//Button Jump
	mJump = ui::Button::create("Button/jump_normal.png", "Button/jump_pressed.png");
	mJump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 80, 150));
	mJump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Jump, this));
	mJump->setOpacity(50);
	addChild(mJump);

	////Button Down
	//mJump = ui::Button::create("Button/jump_normal.png", "Button/jump_pressed.png");
	//mJump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 80, 150));
	//mJump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Jump, this));
	//mJump->setOpacity(50);
	//addChild(mJump);

	//Button Pause
	btnPause = ui::Button::create("Button/pause_norrmal.png", "Button/pause_pressed.png");
	btnPause->setAnchorPoint(Vec2(1, 1));
	btnPause->setPosition(Director::getInstance()->getVisibleSize() - Size(3, 8));
	btnPause->addTouchEventListener(CC_CALLBACK_2(GamePlay::Pause, this));
	addChild(btnPause,2);
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
				tileSet->setPhysicsBody(physic);
				tileSet->setTag(TAG_MAP);
			}
		}
	}
}

bool GamePlay::OnContactBegin(PhysicsContact &contact)
{
	//auto audio = SimpleAudioEngine::getInstance();

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		// charactor vs spider
		if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_CHARACTOR)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 25);
			//audio->playEffect("Sounds/sfx_character_damage.mp3", false, 1.0f, 1.0f, 1.0f);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
			if (this->main_charactor->GetBlood() <= 0)
			{
				log("die");
				if (ControlMusic::GetInstance()->isSound())
				{
					SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
				}
			}
		}
		else if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_SPIDER)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 25);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
			if (this->main_charactor->GetBlood() <= 0)
			{
				log("die");
				if (ControlMusic::GetInstance()->isSound())
				{
					SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
				}
			}
		}


		// main charactor vs diamond
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_DIAMOND)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond++;
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeA->getTag() == TAG_DIAMOND && nodeB->getTag() == TAG_CHARACTOR)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond++;
			nodeA->removeFromParentAndCleanup(true);
		}

		// main charactor vs glass
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_GLASS) {
			nodeB->setPosition(Vec2(-100, -100));
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_into_bush.mp3", false);
			}
		}
		else if (nodeA->getTag() == TAG_GLASS && nodeB->getTag() == TAG_CHARACTOR) {
			nodeA->setPosition(Vec2(-100, -100));
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_into_bush.mp3", false);
			}
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
	auto posY = Director::getInstance()->getVisibleSize().height;

	mHeader = Sprite::create("header.png");
	mHeader->setFlippedX(true);
	mHeader->setAnchorPoint(Vec2(1,1));
	mHeader->setPosition(Director::getInstance()->getVisibleSize());
	mHeader->setVisible(true);
	addChild(mHeader,2);

	Layer *layer_1 = Layer::create();
	auto bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_1->setPercent(100);
	bloodBar_1->setPosition(Director::getInstance()->getVisibleSize() - Size(230,30));

	bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
	bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
	bloodBar_2->setPercent(this->main_charactor->GetBlood());
	bloodBar_2->setPosition(bloodBar_1->getPosition());

	this->addChild(bloodBar_1,3);
	this->addChild(bloodBar_2,2);
}

void GamePlay::CreateNumDiamon()
{
	// sprite diamon
	auto NumDiamon = ResourceManager::GetInstance()->GetSpriteById(3);
	NumDiamon->setScale(0.35);
	NumDiamon->setPosition(bloodBar_2->getPosition() - Vec2(250, 0));
	this->addChild(NumDiamon, 2);

	// label number
	CCString *num = CCString::createWithFormat("%i/50", numDiamond);
	LabelNumDiamon = Label::createWithTTF(num->getCString(), "fonts/Marker Felt.ttf", 30);
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50,0));
	this->addChild(LabelNumDiamon, 2);
}

void GamePlay::createPauseLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//create pause layer
	mPauseLayer = Sprite::create("pause.png");
	mPauseLayer->setPosition(visibleSize / 2);
	mPauseLayer->setContentSize(visibleSize);
	mPauseLayer->setVisible(false);
	addChild(mPauseLayer,2);

	//Button Go to Map
	auto btnHome = ui::Button::create("Button/home_normal.png", "Button/home_pressed.png");
	btnHome->setScale(SCALE_BUTTON);
	btnHome->setPosition(Vec2(visibleSize / 2 - Size(0, 80)));
	btnHome->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
	});
	mPauseLayer->addChild(btnHome);

	//Button Restart
	auto btnRestart = ui::Button::create("Button/restart_normal.png", "Button/restart_pressed.png");
	btnRestart->setScale(SCALE_BUTTON);
	btnRestart->setPosition(btnHome->getPosition() + Size(0, 70));
	btnRestart->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
	});
	mPauseLayer->addChild(btnRestart);

	//Button Resume
	auto btnResume = ui::Button::create("Button/resume_normal.png", "Button/resume_pressed.png");
	btnResume->setScale(SCALE_BUTTON);
	btnResume->setPosition(btnRestart->getPosition() + Size(0, 70));
	btnResume->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		btnPause->setVisible(true);
		mBump->setVisible(true);
		mJump->setVisible(true);
		mPauseLayer->setVisible(false);
	});
	mPauseLayer->addChild(btnResume);
}

void GamePlay::push_rock()
{
	push = false;
	int index = -1;
	index = check_push();
	if (index != -1) {
		push = true;

		Vec2 p_rock = rocks.at(index)->GetSprite()->getPosition();
		Vec2 p_main = main_charactor->GetSprite()->getPosition();

		if (p_rock.x < p_main.x) {
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() -
				Vec2(SPEED_CHARACTOR_RUN, 0));
		}
		else if (p_rock.x > p_main.x) {
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() +
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

	for (int i = 1; i < rocks.size(); i++) {
		float dis = distance(p_main.x, rocks.at(i)->GetSprite()->getPosition().x);
		if (dis < min_horizontal) {
			min_horizontal = dis;
			index = i;
		}
	}

	p_rock = rocks.at(index)->GetSprite()->getPosition();

	if (p_main.y > p_rock.y - 5 && p_main.y < p_rock.y + 5) {
		if (p_rock.x < p_main.x) {
			if ((min_horizontal - rocks.at(0)->getSize().width / 2 - 60) <= _dis_horizontal) {
				return index;
			}
		}
		else if (p_rock.x > p_main.x) {
			if ((min_horizontal + rocks.at(0)->getSize().width / 2) <= _dis_horizontal) {
				return index;
			}
		}
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

void GamePlay::Fight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
	{
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_icehammer.mp3", false);
		}
		fight = true;
		break; 
	}
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
	{
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_hammer.mp3", false);
		}
		fall = false;
		moveUp = true;
		break;
	}
	case ui::Widget::TouchEventType::ENDED:
		fall = true;
		moveUp = false;
		break;
	}
}

void GamePlay::climb()
{
	Vec2 _mainPos = main_charactor->GetSprite()->getPosition();
	Vec2 _mapPos = _tileMap->getPosition();
	Vec2 _winSize = Director::sharedDirector()->getWinSize();

	float _dis_1 = _thang_1.x - (0 - _mapPos.x);
	float _dis_2 = _thang_2.x - (0 - _mapPos.x);
	float _dis_1y = _thang_1.y - (0 - _mapPos.y);
	float _dis_2y = _thang_2.y - (0 - _mapPos.y);

	if (_mainPos.x >= _dis_1 - 30 && _mainPos.x <= _dis_1 + 30 && _mainPos.y <= _dis_1y) {
		main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
	}
	else if (_mainPos.x >= _dis_2 - 30 && _mainPos.x <= _dis_2 + 30 && _mainPos.y <= _dis_2y) {
		main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
	}
	else {
		main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(true);
	}
}

void GamePlay::checkGround()
{
	Vec2 _mapPos = _tileMap->getPosition();
	_collistionGround = false;
	Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
	float dis = distance_1(_main_pos.y, _ground_Pos.y);
	float dis_1 = distance_1(_main_pos.y, _ground_Pos_1.y - (0 - _mapPos.y));
	float dis_2 = distance_1(_main_pos.y, _ground_Pos_2.y - (0 - _mapPos.y));

	if (dis <= 5 && (_main_pos.x > _ground_Pos_2.x && _main_pos.x < _ground_Pos_1.x)) {
		_collistionGround = true;
		if (_main_pos.y < _ground_Pos.y) {
			main_charactor->GetSprite()->setPosition(Vec2(_main_pos.x, _ground_Pos.y));
		}
	}
	else if (dis_1 <= 10 && (_main_pos.x >(_ground_Pos_1.x - (0 - _mapPos.x)))) {
		_collistionGround = true;
		if (_main_pos.y < _ground_Pos_1.y - (0 - _mapPos.y)) {
			main_charactor->GetSprite()->setPosition(Vec2(_main_pos.x, _ground_Pos_1.y - (0 - _mapPos.y)));
		}
	}
	else if (dis_2 <= 10 && (_main_pos.x > 0 && _main_pos.x < _ground_Pos_2.x)) {
		_collistionGround = true;
		if (_main_pos.y < _ground_Pos_2.y) {
			main_charactor->GetSprite()->setPosition(Vec2(_main_pos.x, _ground_Pos_2.y));
		}
	}
}

void GamePlay::Pause(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
			}
			Director::getInstance()->pause();
			//SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		});
		btnPause->setVisible(false);
		mBump->setVisible(false);
		mJump->setVisible(false);
		mPauseLayer->setOpacity(0);
		mPauseLayer->setVisible(true);
		auto fadeIn = FadeIn::create(0.3f);
		mPauseLayer->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}

void GamePlay::update(float deltaTime)

{
	// update main charactor
	main_charactor->Update(deltaTime);
	((MainCharactor *)main_charactor)->setState(fight, moveLeft, moveRight, jump, stun, push);

	// controller
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

	// leo thang
	climb();

	////////////// ground
	checkGround();
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
			mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN + 5);
		}
		else
		{
				float mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
			if (_tileMap->getPosition().y > -(mapHeight - winSize.height - SPEED_CHARACTOR_RUN + 5))
				{
					mapMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN + 5);
				}
				else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height))
				{
					mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN + 5);
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

	else if (main_charactor->GetSprite()->getPosition().y < Director::getInstance()->getWinSize().height / 2 &&
		_tileMap->getPosition().y < 0) {
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			//mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
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
	{//////////////// if() test collision ground
		if(!(_collistionGround && mcMoveDistance == Vec2(0, -SPEED_CHARACTOR_RUN)))
		main_charactor->GetSprite()->setPosition(main_charactor->GetSprite()->getPosition() + mcMoveDistance);
	}

	if (mapMoveDistance != Vec2(0, 0))
	{
		// update map
		_tileMap->setPosition(_tileMap->getPosition() + mapMoveDistance);

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
		mCurrentTouchState = ui::Widget::TouchEventType::CANCELED;
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
