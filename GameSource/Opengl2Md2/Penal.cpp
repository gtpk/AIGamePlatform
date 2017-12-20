#include "ImageControl.h"
#include "Penal.h"
using namespace GameEngine;

namespace GameEngine
{
	Penal::Penal()
	{
		ImageControl();
		m_Container = (ImageControl*)(new Grid());
	}

	void Penal::SetContainer(ImageControl* child)
	{
		m_Container = child;
	}

	void Penal::OnDraw(bool isSelect)
	{
		m_Container->OnDraw(isSelect);
	}

	ImageControl* Penal::GetContainer()
	{
		return m_Container;
	}

	void Penal::addChild(ImageControl* child)
	{
		m_Container->addChild(child);
	}

	std::vector<ImageControl*>  Penal::getAllChild()
	{
		return m_Container->getAllChild();
	}

	void Penal::Remove(ImageControl* child) {
		m_Container->Remove(child);
	}
	ImageControl* Penal::GetImageControlByName(string Name)
	{
		vector<ImageControl*> cc = m_Container->getAllChild();
		vector<ImageControl*>::iterator itor = cc.begin();

		while (itor != cc.end())
		{
			ImageControl* node = *itor;
			if (node->Name == Name)
			{
				return node;
			}
			itor++;
		}
	}
}