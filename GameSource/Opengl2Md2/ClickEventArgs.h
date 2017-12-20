#pragma once
#include "DefExport.h"
#include "MotionEvent.h"
#include "Point.h"
namespace GameEngine
{
	class DllExport ClickEventArgs
	{

	public:
		ClickEventArgs(MotionEvent e)
		{
			m_MotionEvent = e;
		}
		MotionEvent m_MotionEvent;
		Point m_Position;
	};
}