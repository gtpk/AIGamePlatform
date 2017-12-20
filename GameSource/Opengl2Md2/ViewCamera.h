#pragma once
#include <stdio.h>
#include "CommonDataType.h"
#include "DefExport.h"
class DllExport ViewCamera
{
public:
	static ViewCamera* getinstance()
	{
		if (inst == NULL)
		{
			inst = new ViewCamera();
		}
		return inst;
	}

	COMMONDATATYPE::Vector3d eye;

	float ViewScale ;
private:
	static ViewCamera* inst;

	ViewCamera();
	~ViewCamera();


};