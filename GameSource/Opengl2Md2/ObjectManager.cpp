
#include "ObjectManager.h"
#include "Stringformat.h"
#include <map>


ObjectManager* ObjectManager::m_instance = NULL;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::PushGameObejct(const std::string _Name, GameObejct * pObj)
{
	if(isExsistName(_Name))
		return false;

	printf("%s �� ���������� ��� �Ǿ����ϴ�.\n",_Name.c_str());
	m_ObjectNameList[_Name] = pObj;

	pObj->SetName(_Name);

	return true;
}

bool ObjectManager::isExsistName(const std::string _Name)
{
	OBJECT_NAME_MAP_ITOR itor = m_ObjectNameList.find(_Name);
	if(itor != m_ObjectNameList.end())
	{
		//printf("���� �̸��� Object�� �ֽ��ϴ�.");
		return true;
	}
	return false;
}

bool ObjectManager::DeleteGameObejct(const std::string _Name)
{
	printf("%s �� ���������� ���� �Ǿ����ϴ�.\n",_Name.c_str());
	OBJECT_NAME_MAP_ITOR itor = m_ObjectNameList.find(_Name);
	if(itor != m_ObjectNameList.end())
	{
		m_ObjectNameList.erase(itor);
		return true;
	}
	return false;
}

bool ObjectManager::ReplaceGameObejct(const std::string _Name, GameObejct * pObj)
{
	DeleteGameObejct(pObj->GetName());
	PushGameObejct(_Name,pObj);

	printf("%s�� ����Ǿ� ��� �Ǿ����ϴ�.\n",_Name.c_str());

	return true;
}


bool ObjectManager::ObjectdefaultName(GameObejct * pObj)
{
	//�� �̸����� ��ü�� ã���� ����!
	pObj->SetName("(GameObejct)");
	return true;
	//int duplicate = 0;
	//std::string UntitleName;
	//
	//int _size = m_ObjectNameList.size();
	//UntitleName = format("GameObejct%d",_size);
	//
	//while(true)
	//{
	//	if(PushGameObejct(UntitleName,pObj) == false)
	//	{
	//		duplicate++;
	//		UntitleName = format("GameObejct%d(%d)",m_ObjectNameList.size(),duplicate);
	//	}
	//	else
	//	{
	//		pObj->SetName(UntitleName);
	//		return true;
	//	}
	//}
}

