#pragma once
#include "ImageControl.h"
#include <vector>
#include "Grid.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
namespace GameEngine
{
	class DllExport Penal : public ImageControl
	{
	public:
		ImageControl* m_Container;

	public:
		Penal();

	public:
		void SetContainer(ImageControl* child);

		void OnDraw(bool isSelect);

	public:
		ImageControl* GetContainer();

	public:
		void addChild(ImageControl* child);

	public:
		std::vector<ImageControl*>  getAllChild();

	public:
		virtual void Remove(ImageControl* child);

	public:
		ImageControl* GetImageControlByName(string Name);

	};
}