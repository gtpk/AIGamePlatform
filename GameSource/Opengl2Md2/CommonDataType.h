#pragma once
#include "DefExport.h"
#include <iostream>

namespace COMMONDATATYPE
{
	// Camera
	struct DllExport Vector3d
	{
		float x, y, z;

	} typedef Vector3d;

	struct DllExport keyboard_input_t
	{
		unsigned char keymap[256];
		int special[256];
		int modifiers;

	}typedef keyboard_input_t;

	// Mouse
	struct DllExport mouse_input_t
	{
		int buttons[3];
		float x, y;

	} typedef mouse_input_t;

	// Timer
	struct DllExport glut_timer_t
	{
		double current_time;
		double last_time;

	}typedef glut_timer_t;

}