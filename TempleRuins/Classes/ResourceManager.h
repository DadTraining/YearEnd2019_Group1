#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <map>
#include <string.h>

enum Action_Spider {
	S_UP,
	S_DOWN,
	S_SIDE
};

enum Action_Charactor {
	CH_UP,
	CH_RUN,
	CH_DOWN,
	CH_LEFT,
	CH_RIGHT,
	CH_PUSH,
	CH_FIGHT,
	CH_WAIT,
	CH_STUN
};

using namespace std;
USING_NS_CC;
class ResourceManager
{
private:
	string m_dataFolderPath;
	map<int, Sprite*> m_sprites;
	map<int, Sprite*> m_load;
	map<int, Sprite*> m_item;
	map<int, ui::Button*> m_button;
	map<int, Vector<SpriteFrame*>> m_spider_action;
	map<int, Vector<SpriteFrame*>> m_charactor_action;
	map<int, Vector<SpriteFrame*>> m_diamond_action;

	ResourceManager();
	static ResourceManager* instance;
public:
	static ResourceManager* GetInstance();
	void Init(const std::string path);
	void Load(string fileName);
	Sprite* GetSpriteById(int id);
	Sprite* GetItemById(int id);
	ui::Button* GetButtonById(int id);
	Sprite* GetLoadById(int id);
	Vector<SpriteFrame*> GetSpiderUp();
	Vector<SpriteFrame*> GetSpiderDown();
	Vector<SpriteFrame*> GetSpiderSide();
	
	Vector<SpriteFrame*> GetCharactorUp();
	Vector<SpriteFrame*> GetCharactorDown();
	Vector<SpriteFrame*> GetCharactorLeft();
	Vector<SpriteFrame*> GetCharactorRight();
	Vector<SpriteFrame*> GetCharactorPush();
	Vector<SpriteFrame*> GetCharactorFight();
	Vector<SpriteFrame*> GetCharactorWait();
	Vector<SpriteFrame*> GetCharactorRun();
	Vector<SpriteFrame*> GetCharactorStun();
	Vector<SpriteFrame*> GetFrameDiamond();

	std::vector<std::string> Split(std::string str1, std::string str2);
	int Get_ID(string s);
	string Get_Path(string s);
	~ResourceManager();
};

