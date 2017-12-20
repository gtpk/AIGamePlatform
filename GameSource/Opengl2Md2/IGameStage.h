#pragma once
#include "RootUI.h"
#include "DefExport.h"

namespace GameEngine
{
	class DllExport IGameStage  : public  RootUI
	{
	public:

		IGameStage() {} ;
		virtual void onShow() {};
		virtual void onDrawScreen() {};

		virtual void onUpdate(long long dt) {};
		virtual void onClose() {};
		virtual bool isCloseed() { return true; }
		virtual void XboxControllerKeyEvent(WORD Button, bool Updown) {};
	};
}