#include "GamePlay.h"
#include "ControlMusic.h"


cocos2d::Sprite* mPauseLayer;
cocos2d::Sprite* mHeader;
cocos2d::ui::Button *mBump;
cocos2d::ui::Button *btnPause;
cocos2d::Sprite* NumDiamon;

Scene *GamePlay::createGame()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

	//Create Joystick
	CreateJoystick(this);

	// update
	scheduleUpdate();

	// create fire
	fire_normal_1 = new Fire(this, true);
	((Fire*)(fire_normal_1))->setAI(false);
	((Fire*)(fire_normal_1))->setPos(Fire_Normal_1, _tileMap, AI_View);

	fire_normal_2 = new Fire(this, true);
	((Fire*)(fire_normal_2))->setAI(false);
	((Fire*)(fire_normal_2))->setPos(Fire_Normal_2, _tileMap, AI_View);

	fire_normal_3 = new Fire(this, true);
	((Fire*)(fire_normal_3))->setAI(false);
	((Fire*)(fire_normal_3))->setPos(Fire_Normal_3, _tileMap, AI_View);

	fire_ai_1 = new Fire(this, true);
	((Fire*)(fire_ai_1))->setKey(isKey);
	((Fire*)(fire_ai_1))->setAI(true);
	((Fire*)(fire_ai_1))->setPos(Fire_AI_1, _tileMap, AI_View);

	// create key
	key = new Keys(this, true);
	((Keys*)(key))->setPos(Keys_Pos, _tileMap);

	return true;
}

void GamePlay::CreateMap()
{
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map.tmx");
	_background = _tileMap->layerNamed("Background");
	_wall = _tileMap->layerNamed("MapLv1");
	_phy = _tileMap->layerNamed("physics");
	_phy->setVisible(false);
	mObjectGroup = _tileMap->getObjectGroup("Objects");

	mObjectFire = _tileMap->getObjectGroup("Fire");

	mObjectCollistion = _tileMap->getObjectGroup("collisionMapAndCharactor");

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
	// USING ARRAY TO SAVE POSITION OF OBJECT
	wid = (int)_tileMap->getMapSize().width / 2;
	hei = (int)_tileMap->getMapSize().height / 2;
	sizeTilemapWidth = _tileMap->getTileSize().width * 2;
	sizeTilemapHeight = _tileMap->getTileSize().height * 2;

	_arrayMap = new int*[wid];
	for (int i = 0; i < wid; i++) {
		_arrayMap[i] = new int[hei];
	}

	for (int i = 0; i < wid; i++) {
		for (int j = 0; j < hei; j++) {
			_arrayMap[i][j] = NONE;
		}
	}



	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
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
			glass->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
			glasss.push_back(glass);
		}
		else if (type == 5) {//Create Diamond
			Objject* diamon = new Diamond(this);
			diamon->GetSprite()->setPosition(Vec2(posX, posY));
			diamon->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
			diamons.push_back(diamon);
		}
		else if (type == 6) {//Create Rock
			Objject* rock = new Rock(this);
			rock->GetSprite()->setPosition(Vec2(posX, posY));
			rock->GetSprite()->setAnchorPoint(Vec2(0.5f, 0.0f));
			rocks.push_back(rock);
		}
	}

	// get object fire
	auto objects_fire = mObjectFire->getObjects();
	for (int i = 0; i < objects_fire.size(); i++) {
		auto object = objects_fire.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			Fire_Normal_1.push_back(Vec2(posX, posY));
		}else if(type == 2) {
			Fire_AI_1.push_back(Vec2(posX, posY));
		}
		else if (type == 3) {
			Fire_Normal_2.push_back(Vec2(posX, posY));
		}
		else if (type == 4) {
			Fire_dragon_1.push_back(Vec2(posX, posY));
		}
		else if (type == 5) {
			AI_View.push_back(Vec2(posX, posY));
		}
		else if (type == 6) {
			Fire_Normal_3.push_back(Vec2(posX, posY));
		}
		else if (type == 7) {
			Keys_Pos.push_back(Vec2(posX, posY));
		}
		else if (type == 8) {
			blood_1 = Sprite::create("blood.png");
			blood_1->setScale(SCALE_BLOOD);
			blood_1->setTag(TAG_BLOOD);
			blood_1->retain();
			blood_1->setPosition(Vec2(posX, posY));

			auto physic = PhysicsBody::createBox(blood_1->getContentSize());
			physic->setRotationEnable(false);
			physic->setContactTestBitmask(1);
			physic->setDynamic(false);
			blood_1->setPhysicsBody(physic);

			this->addChild(blood_1);
		}
		else if (type == 9) {
			blood_2 = Sprite::create("blood.png");
			blood_2->setScale(SCALE_BLOOD);
			blood_2->setTag(TAG_BLOOD);
			blood_2->retain();
			blood_2->setPosition(Vec2(posX, posY));

			auto physic = PhysicsBody::createBox(blood_2->getContentSize());
			physic->setRotationEnable(false);
			physic->setContactTestBitmask(1);
			physic->setDynamic(false);
			blood_2->setPhysicsBody(physic);

			this->addChild(blood_2);
		}
	}

	// GET OBJECT COLLISTION | MR BIA
	auto object_collistion = mObjectCollistion->getObjects();
	
	for (int i = 0; i < object_collistion.size(); i++) {
		auto object = object_collistion.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		posX = posX / 64;
		posY = posY / 64;
		int X = (int)posX;
		int Y = (int)posY;
		
		collistionCell[X].push_back(Y);

		// USING ARRAY INSTEAD MAP
		_arrayMap[X][Y] = MAP;
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
	//Button Fight
	mBump = ui::Button::create("Button/hammer_normal.png", "Button/hammer_pressed.png");
	mBump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 180, 100));
	mBump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fight, this));
	addChild(mBump);

	//Button Pause
	btnPause = ui::Button::create("Button/pause_norrmal.png", "Button/pause_pressed.png");
	btnPause->setAnchorPoint(Vec2(1, 1));
	btnPause->setPosition(Director::getInstance()->getVisibleSize() - Size(3, 8));
	btnPause->addTouchEventListener(CC_CALLBACK_2(GamePlay::Pause, this));
	addChild(btnPause, 2);
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
		}
		else if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_SPIDER)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 25);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
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
			//nodeB->setVisible(false);
		}
		else if (nodeA->getTag() == TAG_DIAMOND && nodeB->getTag() == TAG_CHARACTOR)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond++;
			nodeA->removeFromParentAndCleanup(true);
			//nodeA->setVisible(false);
		}

		// main charactor vs glass
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_GLASS) {
			//nodeB->removeFromParentAndCleanup(true);
			nodeB->setPosition(-100, -100);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_into_bush.mp3", false);
			}
		}
		else if (nodeA->getTag() == TAG_GLASS && nodeB->getTag() == TAG_CHARACTOR) {
			//nodeA->removeFromParentAndCleanup(true);
			nodeA->setPosition(-100, -100);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_into_bush.mp3", false);
			}
		}

		// main charactor vs fire
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_FIRE) {
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_burn.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 20);
			
		}
		else if (nodeA->getTag() == TAG_FIRE && nodeB->getTag() == TAG_CHARACTOR) {
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_burn.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 20);
		}

		// main charactor vs key
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_KEY) {
			isKey = true;
			nodeB->removeFromParentAndCleanup(true);
			((Fire*)(fire_ai_1))->setKey(isKey);
		}
		else if (nodeA->getTag() == TAG_KEY && nodeB->getTag() == TAG_CHARACTOR) {
			isKey = true;
			nodeA->removeFromParentAndCleanup(true);
			((Fire*)(fire_ai_1))->setKey(isKey);
		}

		// main charactor vs blood
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_BLOOD) {
			nodeB->removeFromParentAndCleanup(true);
			if (this->main_charactor->GetBlood() < 100)
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() + 20);

			if (this->main_charactor->GetBlood() >= 100)
			this->main_charactor->SetBlood(100);
		}
		else if (nodeA->getTag() == TAG_BLOOD && nodeB->getTag() == TAG_CHARACTOR) {
			nodeA->removeFromParentAndCleanup(true);
			if(this->main_charactor->GetBlood() < 100)
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() + 20);

			if (this->main_charactor->GetBlood() >= 100)
			this->main_charactor->SetBlood(100);
		}

		// fight
		if (nodeA->getTag() == TAG_FIGHT && nodeB->getTag() == TAG_SPIDER) {
			nodeB->removeFromParentAndCleanup(true);
			this->numDiamond++;
		}
		else if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_FIGHT) {
			nodeA->removeFromParentAndCleanup(true);
			this->numDiamond++;
		}

	}
	if (this->main_charactor->GetBlood() <= 0)
	{
		log("die");
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
		}
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
	}
	return true;
}

void GamePlay::CreateBloodBar()
{
	auto posY = Director::getInstance()->getVisibleSize().height;

	mHeader = Sprite::create("header.png");
	mHeader->setFlippedX(true);
	mHeader->setAnchorPoint(Vec2(1, 1));
	mHeader->setPosition(Director::getInstance()->getVisibleSize());
	mHeader->setVisible(true);
	addChild(mHeader, 2);

	Layer *layer_1 = Layer::create();
	bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_1->setPercent(100);
	bloodBar_1->setPosition(Director::getInstance()->getVisibleSize() - Size(230, 30));

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
	NumDiamon = ResourceManager::GetInstance()->GetSpriteById(3);
	NumDiamon->setScale(0.35);
	NumDiamon->setPosition(bloodBar_2->getPosition() - Vec2(250, 0));
	this->addChild(NumDiamon, 2);

	// label number
	CCString *num = CCString::createWithFormat("%i/30", numDiamond);
	LabelNumDiamon = Label::createWithTTF(num->getCString(), "fonts/Marker Felt.ttf", 30);
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50, 0));
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
	addChild(mPauseLayer, 2);

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
		mPauseLayer->setVisible(false);
	});
	mPauseLayer->addChild(btnResume);
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
		mPauseLayer->setOpacity(0);
		mPauseLayer->setVisible(true);
		auto fadeIn = FadeIn::create(0.3f);
		mPauseLayer->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}

void GamePlay::update(float deltaTime)

{
	// set view
	this->setViewPointCenter(main_charactor->GetSprite()->getPosition());

	// update blood
	bloodBar_2->setPercent(this->main_charactor->GetBlood());

	// update number diamond
	CCString *num = CCString::createWithFormat("%i/30", numDiamond);
	LabelNumDiamon->setString(num->getCString());

	// update fire AI
	fire_ai_1->Update(deltaTime);
	((Fire*)(fire_ai_1))->setPosMain(this->main_charactor->GetSprite()->getPosition());

	//Update Joystick
	UpdateJoystick(deltaTime);

	// update position of UI when charactor move
	updateUI();

	// UPDATE ARRAY MAP
	this->updateArrayMap();

	// UPDATE POSITION ROCK AND DIAMOND
	this->updatePositionItemByCell();
}

void GamePlay::updateUI()
{
	// UPDATE POSITION OF UI | MR BIA

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto positionUpdate = (ccp(0, 0) - this->getPosition());

	// update fight button
	mBump->setPosition(positionUpdate + visibleSize - ccp(100, 350));

	// update  joystick
	joystickBase->setPosition(positionUpdate + ccp(100, 100));

	// update header
	mHeader->setPosition(positionUpdate + visibleSize);

	// update blood
	bloodBar_1->setPosition(positionUpdate + visibleSize - Size(230, 30));
	bloodBar_2->setPosition(bloodBar_1->getPosition());

	// update button pause
	btnPause->setPosition(positionUpdate + visibleSize - Size(3, 8));

	// number diamond
	NumDiamon->setPosition(bloodBar_2->getPosition() - Vec2(250, 0));
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50, 0));

	// update pause layer
	mPauseLayer->setPosition(positionUpdate + visibleSize / 2);
}

void GamePlay::updateArrayMap()
{
	// clear old position except map's collision
	for (int i = 0; i < wid; i++) {
		for (int j = 0; j < hei; j++) {
			if (_arrayMap[i][j] != MAP) {
				_arrayMap[i][j] = NONE;
			}
		}
	}

	// update position's player
	int posConvertX = (int)(playerPosX / sizeTilemapWidth);
	int posConvertY = (int)(playerPosY / sizeTilemapHeight);
	_arrayMap[posConvertX][posConvertY] = PLAYER;

	// update position's grass
	std::vector<Objject*>::iterator iGlass;
	for (iGlass = glasss.begin(); iGlass != glasss.end(); iGlass++) {
		int x = (*iGlass)->GetSprite()->getPosition().x;
		int y = (*iGlass)->GetSprite()->getPosition().y;

		x = x / sizeTilemapWidth;
		y = y / sizeTilemapHeight;

		// because when charactor collistion vs grass -> move grass to -100, -100
		if(x >= 0 && y >= 0) _arrayMap[x][y] = GRASS;
	}

	// update position's diamond
	std::vector<Objject*>::iterator iDiamond;
	for (iDiamond = diamons.begin(); iDiamond != diamons.end(); iDiamond++) {
		int x = (*iDiamond)->GetSprite()->getPosition().x;
		int y = (*iDiamond)->GetSprite()->getPosition().y;

		x = x / sizeTilemapWidth;
		y = y / sizeTilemapHeight;
		_arrayMap[x][y] = DIAMOND;
	}

	// update position's rock
	std::vector<Objject*>::iterator iRock;
	for (iRock = rocks.begin(); iRock != rocks.end(); iRock++) {
		int x = (*iRock)->GetSprite()->getPosition().x;
		int y = (*iRock)->GetSprite()->getPosition().y;

		x = x / sizeTilemapWidth;
		y = y / sizeTilemapHeight;
		_arrayMap[x][y] = ROCK;
	}
}

void GamePlay::updatePositionItemByCell()
{
	// update position's diamond
	std::vector<Objject*>::iterator iGrass;
	for (iGrass = glasss.begin(); iGrass != glasss.end(); iGrass++) {		// remind: rename glasss to grasss
		int x = (*iGrass)->GetSprite()->getPosition().x;
		int y = (*iGrass)->GetSprite()->getPosition().y;

		x = x / sizeTilemapWidth;
		y = y / sizeTilemapHeight;

		(*iGrass)->GetSprite()->setPosition(x * sizeTilemapWidth + sizeTilemapWidth / 2, y*sizeTilemapHeight);
	}

	// update position's diamond
	std::vector<Objject*>::iterator iDiamond;
	for (iDiamond = diamons.begin(); iDiamond != diamons.end(); iDiamond++) {
		int x = (*iDiamond)->GetSprite()->getPosition().x;
		int y = (*iDiamond)->GetSprite()->getPosition().y;

		x = x / sizeTilemapWidth;
		y = y / sizeTilemapHeight;
		
		(*iDiamond)->GetSprite()->setPosition(x * sizeTilemapWidth + sizeTilemapWidth/2, y*sizeTilemapHeight);
		if (_arrayMap[x][y - 1] == NONE) (*iDiamond)->GetSprite()->setPosition(x * sizeTilemapWidth + sizeTilemapWidth / 2, y*sizeTilemapHeight - 10);
	}


	// update position's rock
	std::vector<Objject*>::iterator iRock;
	for (iRock = rocks.begin(); iRock != rocks.end(); iRock++) {
		int x = (*iRock)->GetSprite()->getPosition().x;
		int y = (*iRock)->GetSprite()->getPosition().y;

		x = x / sizeTilemapWidth;
		y = y / sizeTilemapHeight;

		(*iRock)->GetSprite()->setPosition(x * sizeTilemapWidth + sizeTilemapWidth / 2, y*sizeTilemapHeight);
		if (_arrayMap[x][y - 1] == NONE) (*iRock)->GetSprite()->setPosition(x * sizeTilemapWidth + sizeTilemapWidth / 2, y*sizeTilemapHeight - 10);
	}
}

void GamePlay::setViewPointCenter(CCPoint position)
{
	CCSize winSize = Director::getInstance()->getVisibleSize();

	Vec2 mapMoveDistance = Vec2(0, 0);
	Vec2 mcMoveDistance = Vec2(0, 0);

	// FIX ACROSS THE WALL | MR BIA
	int posXPlayer = main_charactor->GetSprite()->getPosition().x;
	int posYPlayer = main_charactor->GetSprite()->getPosition().y;

	int posXCellOfCharactor = posXPlayer / sizeTilemapWidth;
	int posYCellOfCharactor = posYPlayer / sizeTilemapHeight;
	
	bool checkMove = true;

	if (moveRight)
	{	
		//if (collistionCell.size() > 0) {
		//	listCell = collistionCell.find(posXCellOfCharactor+1)->second;
		//	list<int>::iterator ll = listCell.begin();
		//	for (ll; ll != listCell.end(); ll++) {
		//		//log("here is it %d", *ll);
		//		if (*ll == (posYCellOfCharactor)) {
		//			checkMove = false;
		//			break;
		//		}
		//	}
		//}
		if (_arrayMap[posXCellOfCharactor + 1][posYCellOfCharactor] == MAP ||
			_arrayMap[posXCellOfCharactor + 1][posYCellOfCharactor] == ROCK) checkMove = false;
		if (checkMove == true) main_charactor->GetSprite()->setPosition(posXPlayer + 5, posYPlayer);

		// STATE MOVE RIGHT
		main_charactor->mvRight();
	}
	else if (moveLeft)
	{
		//if (collistionCell.size() > 0) {
		//	listCell = collistionCell.find(posXCellOfCharactor-1)->second;
		//	list<int>::iterator ll = listCell.begin();
		//	for (ll; ll != listCell.end(); ll++) {
		//		//log("here is it %d", *ll);
		//		if (*ll == (posYCellOfCharactor)) {
		//			checkMove = false;
		//			break;
		//		}
		//	}
		//}
		if (_arrayMap[posXCellOfCharactor - 1][posYCellOfCharactor] == MAP ||
			_arrayMap[posXCellOfCharactor - 1][posYCellOfCharactor] == ROCK) checkMove = false;
		if (checkMove == true) main_charactor->GetSprite()->setPosition(posXPlayer - 5, posYPlayer);
		
		// STATE MOVE LEFT
		main_charactor->mvLeft();
	}
	else if (moveUp || jump)
	{
		//if (collistionCell.size() > 0) {
		//	listCell = collistionCell.find(posXCellOfCharactor)->second;
		//	list<int>::iterator ll = listCell.begin();
		//	for (ll; ll != listCell.end(); ll++) {
		//		//log("here is it %d", *ll);
		//		if (*ll == (posYCellOfCharactor + 1)) {
		//			checkMove = false;
		//			break;
		//		}
		//	}
		//}
		if (_arrayMap[posXCellOfCharactor][posYCellOfCharactor + 1] == MAP ||
			_arrayMap[posXCellOfCharactor][posYCellOfCharactor + 1] == ROCK) checkMove = false;
		if(checkMove == true) main_charactor->GetSprite()->setPosition(posXPlayer, posYPlayer + 5);
	
	}
	else if (moveDown)
	{
		//list<int>::iterator ll;
		//if (collistionCell.size() > 0) {
		//	listCell = collistionCell.find(posXCellOfCharactor)->second;
		//	ll = listCell.begin();
		//	for (ll; ll != listCell.end(); ll++) {
		//		//log("here is it %d", *ll);
		//		if (*ll == (posYCellOfCharactor - 1)) {
		//			checkMove = false;
		//			break;
		//		}
		//	}
		//}
		if (_arrayMap[posXCellOfCharactor][posYCellOfCharactor - 1] == MAP ||
			_arrayMap[posXCellOfCharactor][posYCellOfCharactor - 1] == ROCK) checkMove = false;
		if (checkMove == true) main_charactor->GetSprite()->setPosition(posXPlayer, posYPlayer - 5);
	}
	else {
		// MOVE BY CELL   | Mr Bia
		playerPosX = main_charactor->GetSprite()->getPosition().x;
		playerPosY = main_charactor->GetSprite()->getPosition().y;
		
		int posConvertX = (int)(playerPosX / sizeTilemapWidth);
		int posConvertY = (int)(playerPosY / sizeTilemapHeight);
		main_charactor->GetSprite()->setPosition(posConvertX*(sizeTilemapWidth)+sizeTilemapWidth/2, posConvertY*sizeTilemapHeight);
		
		// STATE IDLE
		main_charactor->idle();
	}

	int posX = main_charactor->GetSprite()->getPosition().x;
	int posY = main_charactor->GetSprite()->getPosition().y;
	int x = MAX(posX, winSize.width / 2);
	int y = MAX(posY, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width*this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height*this->_tileMap->getTileSize().height) - winSize.height / 2);
	
	CCPoint actualPosition = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void GamePlay::CreateJoystick(Layer * layer)
{
	auto thumb = Sprite::create("thumb.png");
	auto joystick = Sprite::create("joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(MARGIN_JOYSTICK + thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, MARGIN_JOYSTICK + thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(Vec2(100,100));
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setAnchorPoint(Vec2(0, 0));
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.2f);
	joystickBase->setScale(1.0f);
	joystick->setScale(0.5f);
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(Vec2(100,100));

	leftJoystick = joystickBase->getJoystick();
	activeRunRange = thumb->getBoundingBox().size.height / 2;
	
	layer->addChild(joystickBase);
}

void GamePlay::UpdateJoystick(float dt)
{
	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if (degree > 135 && degree < 180 || degree > -180 && degree < -135)//MoveLeft
		{
			moveRight = false;
			moveLeft = true;
			moveUp = false;
			moveDown = false;
		}
		if (degree > -135 && degree < -45 )//Move Down
		{
			moveRight = false;
			moveLeft = false;
			moveUp = false;
			moveDown = true;
		}
		if (degree > -45 && degree < 45)//Move Right
		{
			moveRight = true;
			moveLeft = false;
			moveUp = false;
			moveDown = false;
		}
		if (degree > 45 && degree < 135)//Move Up
		{
			moveRight = false;
			moveLeft = false;
			moveUp = true;
			moveDown = false;
		}
	}
	else
	{
		moveRight = false;
		moveLeft = false;
		moveUp = false;
		moveDown = false;
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