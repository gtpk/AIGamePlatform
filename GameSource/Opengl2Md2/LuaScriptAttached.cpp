#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"

#include "./AttacheAble.h"
#include "LuaScriptAttached.h"

#include "Md2Model.h"
#include "PieceModel.h"
#include "Md2Object.h"


LuaScriptAttached::LuaScriptAttached()
	: NowStatus(NULL)
{

	NowStatus = LuaManager::Getinstance();
    
}

int LuaScriptAttached::GetSize()
{
	return 0;
}


void LuaScriptAttached::OnAttach(GameObejct* object)
{

	
	
}

LuaScriptAttached::~LuaScriptAttached()
{
	
}
