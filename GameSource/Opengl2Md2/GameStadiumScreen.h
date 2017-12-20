#pragma once
#include "Point.h"
#include "Opengl2md2.h"
#include "ExGameGraphicInfo.h"
#include "KardNameFactory.h"
#include "StageManager.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <cstdarg>
#include <cerrno>
#include <cmath>
#include <math.h>
#include "SelectableObject.h"
#include "DefExport.h"

using namespace std::chrono;
using namespace GameEngine;


namespace GameEngine
{
	class DllExport GameStadiumScreen : public SelectableObject
	{
	public:
		GameStadiumScreen();

	private:
		long long ElpseTimer;
		COMMONDATATYPE::Vector3d _p;
		COMMONDATATYPE::Vector3d GetNowPostion() { return _p; }
		void SetNowPostion(COMMONDATATYPE::Vector3d pos) {}
	public:
		void onDrawFrame();

		int _SelectID;


		static int glPrintf(const char *format, ...);
		void onSurfaceChanged(int width, int height);

		void onSurfaceCreated();
		bool m_isPressd;

		bool onTouchEvent(MotionEvent _event);

		void XboxControllerKeyEvent(WORD Button, bool Updown);

		void deleteSelectPiece();
	};

}