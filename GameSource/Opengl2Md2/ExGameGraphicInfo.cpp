#include "ExGameGraphicInfo.h"
#include "Point.h"

using namespace GameEngine;


namespace GameEngine
{
	ExGameGraphicInfo* ExGameGraphicInfo::m_GameGraphic = 0;

	void ExGameGraphicInfo::SetGameSize(GameEngine::Point GameSize)
	{
		m_GameSize = GameSize;
		//HORIZEN? VERTICAL?
		bool ishorizen = false;

		GameEngine::Point GameResolution(1280, 720);

		GameEngine::Point TotalSize(ExGameGraphicInfo::GetGameGraphic()->GetGameSize());

		Resolution = (float)TotalSize.x / (float)GameResolution.x;

		if (GameResolution.y * Resolution < TotalSize.y)
		{
			ishorizen = false;
		}
		else
		{
			ishorizen = true;
			Resolution = (float)TotalSize.y / (float)GameResolution.y;
		}

		int BlackScreanX = 0, BlackScreanY = 0;


		if (ishorizen)
		{
			BlackScreanX = (int)(TotalSize.x - (GameResolution.x * Resolution)) / 2;
		}
		else
		{
			BlackScreanY = (int)(TotalSize.y - (GameResolution.y * Resolution)) / 2;
		}
		m_BlackScreanSize = GameEngine::Point(BlackScreanX, BlackScreanY);

		m_ActuralBlackSize = GameEngine::Point();
		if (BlackScreanX != 0)
			m_ActuralBlackSize.x = (int)((TotalSize.x - (GameResolution.x * Resolution)) / Resolution / 2);
		if (BlackScreanY != 0)
			m_ActuralBlackSize.y = (int)((TotalSize.y - (GameResolution.y * Resolution)) / Resolution / 2);

	}
}