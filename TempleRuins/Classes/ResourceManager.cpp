#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager * ResourceManager::GetInstance()
{
	if (!instance) {
		instance = new ResourceManager;
	}
	return instance;
}

void ResourceManager::Init(const std::string path)
{
	this->m_dataFolderPath = path;
	Load(m_dataFolderPath);
}

void ResourceManager::Load(string fileName)
{
	string s = FileUtils::getInstance()->getStringFromFile(fileName);
	vector<std::string> arr_source = Split(s, "\r\n");

	for (size_t i = 0; i < arr_source.size(); i++) {
		// get name and number
		vector<std::string> arr_name = Split(arr_source[i], " ");

		if (arr_name[0] == "#SPRITE") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				string path = Get_Path(arr_source[i]);

				// create sprite
				auto sprite = Sprite::create(path);
				sprite->retain();

				// insert map
				m_sprites.insert(pair<int, Sprite*>(id, sprite));

				number--;
			}
		}
		else if (arr_name[0] == "#LOAD") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				string path = Get_Path(arr_source[i]);

				// create sprite
				auto sprite = Sprite::create(path);
				sprite->retain();

				// insert map
				m_load.insert(pair<int, Sprite*>(id, sprite));

				number--;
			}
		}
		else if (arr_name[0] == "#BUTTON") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				string path = Get_Path(arr_source[i]);

				// create sprite
				auto button = ui::Button::create(path, "");
				button->retain();

				// insert map
				m_button.insert(pair<int, ui::Button*>(id, button));

				number--;
			}
		}
		else if (arr_name[0] == "#ITEM") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				string path = Get_Path(arr_source[i]);

				// create sprite
				auto item = Sprite::create(path);
				item->retain();

				// insert map
				m_item.insert(pair<int, Sprite*>(id, item));

				number--;
			}
		}
		else if (arr_name[0] == "#MAIN_ACTION_PUSH") {
			// number 
			int number = atoi(arr_name[1].c_str());
			while (number > 0) {
				i++;                  // id
				int id = Get_ID(arr_source[i]);

				i++;                  // path
				string path = Get_Path(arr_source[i]);

				// load plist
				auto spriteCache = SpriteFrameCache::getInstance();
				spriteCache->addSpriteFramesWithFile(path);

				// create
				auto push_1 = Sprite::createWithSpriteFrameName("1.png");
				auto push_2 = Sprite::createWithSpriteFrameName("2.png");
				auto push_3 = Sprite::createWithSpriteFrameName("3.png");
				auto push_4 = Sprite::createWithSpriteFrameName("4.png");
				auto push_5 = Sprite::createWithSpriteFrameName("5.png");
				auto push_6 = Sprite::createWithSpriteFrameName("6.png");

				Vector<SpriteFrame*> spriteFrames;
				spriteFrames.pushBack((SpriteFrame*)push_1);
				spriteFrames.pushBack((SpriteFrame*)push_2);
				spriteFrames.pushBack((SpriteFrame*)push_3);
				spriteFrames.pushBack((SpriteFrame*)push_4);
				spriteFrames.pushBack((SpriteFrame*)push_5);
				spriteFrames.pushBack((SpriteFrame*)push_6);
				
				auto animation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
				auto animate = Animate::create(animation);
				auto repeatForeverActionPush = RepeatForever::create(animate);
				repeatForeverActionPush->retain();

				// insert map
				m_action_push.insert(pair<int, RepeatForever*>(id, repeatForeverActionPush));

				number--;
			}
		}
	}
}

Sprite * ResourceManager::GetSpriteById(int id)
{
	return m_sprites.at(id);
}

Sprite * ResourceManager::GetItemById(int id)
{
	return m_item.at(id);
}

ui::Button * ResourceManager::GetButtonById(int id)
{
	return m_button.at(id);
}

Sprite * ResourceManager::GetLoadById(int id)
{
	return m_load.at(id);
}

RepeatForever * ResourceManager::GetActionPushById(int id)
{
	return m_action_push.at(id);
}

std::vector<std::string> ResourceManager::Split(std::string str1, std::string str2)
{
	vector<std::string> arr;

	char *c = const_cast<char*>(str1.c_str());
	char* s1 = strtok(c, str2.c_str());

	while (s1 != NULL) {
		arr.push_back(s1);
		s1 = strtok(NULL, str2.c_str());
	}


	return arr;
}

int ResourceManager::Get_ID(string s)
{
	int id;
	std::vector<std::string> arr_id = Split(s, " ");
	id = atoi(arr_id[1].c_str());

	return id;
}

string ResourceManager::Get_Path(string s)
{
	string path = "";
	std::vector<std::string> arr_path = Split(s, " ");
	path = arr_path[1];

	return path;
}


ResourceManager::~ResourceManager()
{
}
