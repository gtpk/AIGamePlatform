#pragma once
#include <vector>
#include "PointF.h"
#include "DefExport.h"

namespace GameEngine
{
	class ImageControl;

	class DllExport IContainer : public PointF
	{
	public:
		virtual void addChild(GameEngine::ImageControl* child) = 0;

		virtual std::vector<GameEngine::ImageControl*>  getAllChild() = 0;

		virtual void OnDraw(bool isSelect = false) = 0;

		virtual void Remove(GameEngine::ImageControl* child) = 0;

		virtual bool AllAnimationFinished() = 0;
	};
}