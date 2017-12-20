#include "LoadingScreen.h"
#include "XBoxControllerManager.h"
#include "GameWorld.h"
#include "StageManager.h"

using namespace GameEngine;
namespace GameEngine
{
	void LoadingScreen::onShow()
	{
		Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();
	}

	void LoadingScreen::eventReceived(UIBase* sender, ClickEventArgs e)
	{

	}


	void LoadingScreen::XboxControllerKeyEvent(WORD Button, bool Updown)
	{
	}

	void LoadingScreen::onUpdate(long long dt)
	{
		if (KardNameFactory::GetKardNameFactory()->IsLoaded == false)
		{
			return;
		}
	}
}