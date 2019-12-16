#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <map>
#include <string.h>

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

	ResourceManager();
	static ResourceManager* instance;
public:
	static ResourceManager* GetInstance();
	void Init(const std::string path);
	void Load(string fileName);
	Sprite* GetSpriteById(int id);
	Sprite* GetItemById(int id);
	ui::Button* GetButtonById(int id);

	std::vector<std::string> Split(std::string str1, std::string str2);
	int Get_ID(string s);
	string Get_Path(string s);
	~ResourceManager();
};

