#pragma once
#include <map>
#include <unordered_map>
#include "GameObejct.h"
using namespace std;

class DllExport ObjectNumberingMananger
{
public:
	ObjectNumberingMananger();
	~ObjectNumberingMananger();

private:
	static ObjectNumberingMananger* inst;
public:
	static ObjectNumberingMananger* getInstance()
	{
		if (inst == NULL)
		{
			inst = new ObjectNumberingMananger();
		}
		return inst;
	}

	bool isExsistNumber(int number);
	bool UseNumber(int number, GameObejct* obj);
	bool UnUseNumber(int number, GameObejct* obj);
	int getNumber(GameObejct* obj);
	GameObejct* GetGameObejct(int Name);
private:
	// Member variables
	std::map<int, bool> CheckMap;
	int _NextID;
	std::map<int, GameObejct*> ObjectList;
	

};
