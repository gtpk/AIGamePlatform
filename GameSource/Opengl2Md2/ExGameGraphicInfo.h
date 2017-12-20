#pragma once
#include <iostream>
#include <algorithm>    // std::sort
#include <cstdarg>
#include <cerrno>
#include <cmath>
#include <math.h>
#include "Point.h"

#include "DefExport.h"

namespace GameEngine
{
	class DllExport ExGameGraphicInfo
	{


	private:
		static ExGameGraphicInfo* m_GameGraphic;

	public:
		ExGameGraphicInfo()
		{
			m_GameSize.x = 1270;
			m_GameSize.y = 720;
			Resolution = 1.0f;
		}

		static ExGameGraphicInfo* GetGameGraphic()
		{

			if (m_GameGraphic == 0)
				m_GameGraphic = new ExGameGraphicInfo();

			return m_GameGraphic;
		}


		////////////////////////////////////////////////////////////

		Point m_GameSize;
		Point m_BlackScreanSize;

		Point m_ActuralBlackSize;
		Point m_ActuralPos;

		float Resolution;

		void SetGameSize(Point GameSize);

		Point GetBlackActuralBlackSize()
		{
			return m_ActuralBlackSize;
		}

		float GetResolution()
		{
			return Resolution;
		}

		Point GetBlackScreanSize()
		{
			return m_BlackScreanSize;
		}

		Point GetGameSize()
		{
			return m_GameSize;
		}





	};

}