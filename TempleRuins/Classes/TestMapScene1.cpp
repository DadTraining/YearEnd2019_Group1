#include "TestMapScene1.h"

bool left1 = false;
bool right1 = false;
bool up = false;
bool down = false;


Scene * TestMapScene1::createMap()
{
	CCScene * scene = CCScene::create();
	TestMapScene1* layer = TestMapScene1::create();
	scene->addChild(layer);
	return scene;
}

bool TestMapScene1::init()
{
	if (!CCLayer::init()) {
		return false;
	}

	map = new CCTMXTiledMap();
	map->initWithTMXFile("map.tmx");
	//map->setScale(0.5);
	background = map->layerNamed("Background");
	wall = map->layerNamed("MapLv1");
	meta = map->layerNamed("physics");
	meta->setVisible(true);
	//wall->setVisible(false);

	this->addChild(map);

	auto objectgroup = map->objectGroupNamed("Objects");
	if (objectgroup == NULL) {
		log("no object grouppppppppppppppppppppppppppp");
		return false;
	}
	auto spawPoint = objectgroup->objectNamed("SpawnPoint");
	int x = spawPoint.at("x").asDouble();
	int y = spawPoint.at("y").asDouble();

	mainCh = ResourceManager::GetInstance()->GetSpriteById(3);
	mainCh->setScale(0.15);
	mainCh->setPosition(ccp(x, y));
	this->addChild(mainCh);



	this->setViewPointCenter(mainCh->getPosition());


	

	//keyboard
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(TestMapScene1::OnKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(TestMapScene1::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);





	scheduleUpdate();
	return true;
}


void TestMapScene1::update(float deltaTime)
{
	static float k = 0;
	k += deltaTime;
	if (k >= 0.1) {
		CCPoint playerPos = mainCh->getPosition();
		if (left1) {
			playerPos.x -= map->getTileSize().width;
		}
		else if (right1) {
			playerPos.x += map->getTileSize().width;
		}
		else if (up) {
			playerPos.y += map->getTileSize().height;
		}
		else if (down) {
			playerPos.y -= map->getTileSize().height;
		}

		if (playerPos.x <= (map->getMapSize().width * map->getTileSize().width) &&
			playerPos.y <= (map->getMapSize().height * map->getTileSize().height) &&
			playerPos.y >= 0 && playerPos.x >= 0)
		{
			this->setPlayerPosition(playerPos);
		}
		this->setViewPointCenter(mainCh->getPosition());
		k = 0;
	}
}

void TestMapScene1::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A: {
		left1 = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {
		right1 = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W: {
		up = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {
		down = true;
		break;
	}
	default:
		break;
	}
}

void TestMapScene1::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_A: {
		left1 = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {
		right1 = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W: {
		up = false;
		break;
	}

	case EventKeyboard::KeyCode::KEY_S: {
		down = false;
		break;
	}
	default:
		break;
	}
}

void TestMapScene1::setViewPointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (map->getMapSize().width * this->map->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (map->getMapSize().height * map->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void TestMapScene1::setPlayerPosition(CCPoint position)
{
	CCPoint tileCoord = this->tileCoorforposition(position);
	int tileGid = meta->tileGIDAt(tileCoord);
	if (tileGid) {
		auto properties = map->propertiesForGID(tileGid);
		if (!properties.isNull()) {
			ValueMap dict = properties.asValueMap();
			Value collision = dict["collidable"];
			if (!collision.isNull() && collision.asString() == "true") {
				return;
			}
		}
	}
	mainCh->setPosition(position);
}

CCPoint TestMapScene1::tileCoorforposition(CCPoint position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;

	return ccp(x, y);
}

TestMapScene1::TestMapScene1()
{
}

TestMapScene1::~TestMapScene1()
{
}
