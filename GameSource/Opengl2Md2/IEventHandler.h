#pragma once
#include "UIBase.h"
#include "DefExport.h"

using namespace GameEngine;
namespace GameEngine
{
	template<class T>
	class DllExport IEventHandler
	{
	public:
		virtual void eventReceived(UIBase* sender, T e) = 0;
	private:

	};
}