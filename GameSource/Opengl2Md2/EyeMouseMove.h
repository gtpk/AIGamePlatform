#pragma once
#include <stdio.h>
#include "CommonDataType.h"
#include "DefExport.h"

class DllExport EyeMouseMove
{
public:
	
	~EyeMouseMove();
	COMMONDATATYPE::Vector3d	old_eye;
	COMMONDATATYPE::mouse_input_t Last_mouse;
	static EyeMouseMove* getinstance()
	{
		if (inst == NULL)
		{
			inst = new EyeMouseMove();
		}
		return inst;
	}

	void SetMousePos(float x, float y , bool isClick);
	void Enable();
	void Disable();
private:

	bool isActive;
	EyeMouseMove();
	static EyeMouseMove* inst;

	
};


