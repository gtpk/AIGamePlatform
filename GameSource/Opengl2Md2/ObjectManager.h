#pragma once
#include "GameObejct.h"

#include <map>
#include "DefExport.h"

class GameObejct;

class DllExport ObjectManager
{
public:

	typedef std::map<std::string, GameObejct*> OBJECT_NAME_MAP;
	typedef OBJECT_NAME_MAP::iterator OBJECT_NAME_MAP_ITOR;


public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* GetInstance()
	{
		if(m_instance == NULL)
		{
			m_instance = new ObjectManager();
		}
		return m_instance;
	}
	

	OBJECT_NAME_MAP m_ObjectNameList;

	bool PushGameObejct(const std::string _Name, GameObejct * pObj);

	bool isExsistName(const std::string _Name);

	bool DeleteGameObejct(const std::string _Name);

	bool ReplaceGameObejct(const std::string _Name, GameObejct * pObj);

	bool ObjectdefaultName(GameObejct * pObj);

	

private:
	static ObjectManager* m_instance;
};

