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
	class DllExport InGameUI : public IGameStage
	{
	public:

		long long dt_timesleep;
		
	public:
		InGameUI()
		{
			addEventHandler(dynamic_cast<IEventHandler<ClickEventArgs>*> (this));
			dt_timesleep = 200;
			CarmeraViewAniX = NULL;
			CarmeraViewAniY = NULL;
			CarmeraViewAniScale = NULL;
		}
		Animation* CarmeraViewAniX ;
		Animation* CarmeraViewAniY ;
		Animation* CarmeraViewAniScale ;
		Md2Object* king;
	public:


		void onDrawScreen()
		{
			OnDraw(false);
		}



	public:

		void XboxControllerKeyEvent(WORD Button, bool Updown);
		void onShow();

		void eventReceived(UIBase* sender, ClickEventArgs e);

		void onUpdate(long long dt);

		void onClose() {
		}

		bool isCloseed() {
			return true;

		}
	};

}