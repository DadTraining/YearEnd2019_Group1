#include "Fire.h"



void Fire::Init()
{
	this->SetSprite(Sprite::create("button.png"));
	this->GetSprite()->retain();
	
	// run action
	auto animation = Animation::createWithSpriteFrames(ResourceManager::GetInstance()->GetActionFire(), 0.2);
	auto animate = Animate::create(animation);
	animate->retain();
	this->GetSprite()->runAction(RepeatForever::create(animate));
	this->GetSprite()->setScale(0.1);
	//this->layer->addChild(this->GetSprite());
}

void Fire::Update(float deltaTime)
{
	if (isAI()) {
		runAI();
	}
}

Fire::Fire(Layer* layer)
{
	this->layer = layer;
	Init();
}

Size Fire::getSize()
{
	return Size();
}

void Fire::setPos(vector<Vec2> Fire_pos, CCTMXTiledMap *_tileMap)
{
	this->Fire_pos = Fire_pos;
	this->_tileMap = _tileMap;
	this->GetSprite()->setPosition(Fire_pos.at(0));
	this->_tileMap->addChild(this->GetSprite(), 5);

	if (!isAI()) {
		auto moveTo_1 = MoveTo::create(1, Fire_pos.at(1));
		auto moveTo_2 = MoveTo::create(1, Fire_pos.at(2));
		auto moveTo_3 = MoveTo::create(1, Fire_pos.at(3));
		auto moveTo_4 = MoveTo::create(1, Fire_pos.at(0));
		auto sq = Sequence::create(moveTo_1, moveTo_2, moveTo_3, moveTo_4, nullptr);

		this->GetSprite()->runAction(RepeatForever::create(sq));
	}
}

void Fire::setPosMain(Vec2 pos_main)
{
	this->pos_main = pos_main;
}


void Fire::setAI(bool c)
{
	this->AI = c;
}

bool Fire::isAI()
{
	return AI;
}

void Fire::runAI()
{
	Vec2 pos_AI = this->GetSprite()->getPosition();
	log("%f        %f", pos_AI.x, pos_AI.y );
	if (distance(pos_main, pos_AI) < 200) {
		log("oke man");
		auto mapPOS = _tileMap->getPosition();
		auto x = pos_main.x;
		auto y = pos_main.y;
		auto moveTo = MoveTo::create(1, Vec2(pos_AI.x - 1, pos_AI.y - 1));
		this->GetSprite()->runAction(moveTo);
		log("xxxxxxxxxxxxx %f      yyyyyyyy  %f", x,y);
		//log("%f        %f       %f       %f       %f       %f", pos_AI.x, pos_AI.y, x, y, pos_main.x+(0-mapPOS.x), pos_main.y + (0 - mapPOS.y));
	}
}

float Fire::distance(Vec2 main, Vec2 AI)
{
	auto mapPOS = _tileMap->getPosition();
	float dis = sqrt((main.x - (AI.x - (0 - mapPOS.x)))*(main.x - (AI.x - (0 - mapPOS.x))) + (main.y - (AI.y - (0 - mapPOS.y)))*(main.y - (AI.y - (0 - mapPOS.y))));
	//log("%f        %f", AI.x - (0 - mapPOS.x), AI.y - (0 - mapPOS.y));
	
	return dis;
}

Fire::~Fire()
{
}
