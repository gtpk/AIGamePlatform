#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"
#include "./AttacheAble.h"
#include "DefExport.h"

class TestFunctionClass
{
};

class DllExport LuaScriptAttached : public AttacheAble
{

public:
	LuaScriptAttached();
	~LuaScriptAttached();

	virtual void OnAttach(GameObejct* object);

	

	int GetSize();
private:

	LuaManager* NowStatus;

};

