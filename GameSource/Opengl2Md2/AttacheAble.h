#pragma once
#include "DefExport.h"
#include "./GameObejct.h"
#include "LuaManager.h"

class GameObejct;

class DllExport AttacheAble
{
public:
	AttacheAble(void);
	virtual ~AttacheAble(void);

	virtual void OnAttach(GameObejct* object) = 0;
	

private:
	
};

