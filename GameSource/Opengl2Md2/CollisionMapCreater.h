#pragma once
#include "DefExport.h"
#include "CommonDataType.h"
#include "CollisionMap.h"
#include <vector>
class DllExport CollisionMapCreater
{
public:
	CollisionMapCreater();
	~CollisionMapCreater();



	void onDraw(); 
	void SetVertext(COMMONDATATYPE::Vector3d dot);
	void SetVertext(float x,float y);

	void NewCollisionMap();

	void SelectCollistionMap(int select) { selectNumber = select; }
	void SelectPoint(float x,float y);

	static CollisionMapCreater* getinstance()
	{
		if (inst == NULL)
		{
			inst = new CollisionMapCreater();
		}
		return inst;
	}
private:

	int selectNumber;
	std::vector<CollisionMap*> dotlist;

	static CollisionMapCreater* inst;
	
};