#pragma once
#include "IGameStage.h"
#include "ImageControl.h"
#include "Snumber.h"
#include "defAnimations.h"
#include "KardNameFactory.h"
#include "UIBase.h"
#include "DefExport.h"

namespace GameEngine
{
	class DllExport MainScreen : public IGameStage
	{
	public:

		int LoadingPersent;

		long long dt_timesleep ;

		ImageControl* Background;
		ImageControl* title;
		ImageControl* PressAny;
		ImageControl* MainMenu;
		ImageControl* TitleWheel;
		ImageControl* MainMenuOption;
		ImageControl* MainMenuStart;
		ImageControl* MainMenuExit;

		Animation * Spacial;
		Animation * UPAni;
	public:
		MainScreen()
		{

			LoadingPersent = 0;


			addEventHandler(dynamic_cast<IEventHandler<ClickEventArgs>*> (this));
			dt_timesleep = 2000;
			selectValue = 0;
			//KardNameFactory.GetKardNameFactory().PlayOppeningSound();
			//KardNameFactory.GetKardNameFactory().StopBackgroundSound();
		}

	public:


		void onDrawScreen()
		{

			OnDraw(false);
			//King->OnDraw();
		}

		int selectValue;


	public:

		void XboxControllerKeyEvent(WORD Button, bool Updown);
		void onShow();

		void eventReceived(UIBase* sender, ClickEventArgs e);

		void onUpdate(long long dt);

		void onClose() {
			// TODO Auto-generated method stub

		}

		bool isCloseed() {
			// TODO Auto-generated method stub
			return true;

		}
	};

}