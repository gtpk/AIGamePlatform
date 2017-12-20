#pragma once

#include <random>
#include <string>
#include <vector>
#include <unordered_map>
#include "ImageLoader.h"
#include "AtlasObj.h"

#include "GL/glew.h"
#include "GL/glut.h"
#include "DefExport.h"

using namespace std;
namespace GameEngine
{
	class DllExport ImageLoader
	{

	private:
		bool isForceClose;
		vector<int> m_ResourseList;
		int m_Count;
		int m_MaxCount;

		bool oldstyle;

	public:
		ImageLoader();

		void stopThread();
		/*
		public Bitmap[] GetBitmapRsualt() {
		if (m_Count >= m_MaxCount) {
		return KARD_output.toArray(new Bitmap[KARD_output.size()]);
		} else {
		return null;
		}
		}*/

		float GetLoadingPercent();
		void run();
	};

}