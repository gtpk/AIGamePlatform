#include "ObjectMove.h"

ObjectMove* ObjectMove::inst = NULL;
ObjectMove::ObjectMove()
{
}

ObjectMove::~ObjectMove()
{
}

void ObjectMove::OnDraw()
{
	std::list<SelectableObject*>::iterator md2begin = GameWorld::getInstance().child.begin();

	for (; md2begin != GameWorld::getInstance().child.end(); md2begin++)
	{
		Md2Object* node = (Md2Object*)*md2begin;

		node->SelectDraw();
	}
}