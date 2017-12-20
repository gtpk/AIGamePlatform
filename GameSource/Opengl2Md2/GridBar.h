#pragma once
#include "DefExport.h"

namespace GameEngine
{
	enum GridBarType
	{
		Horizontal,
		Vertical
	};

	class DllExport GridBar
	{
	public:
		GridBarType MARXAnimatnionType;
		float Value;

		GridBar(float _value, GridBarType _type)
		{
			Value = _value;
			MARXAnimatnionType = _type;
		}

	};
}