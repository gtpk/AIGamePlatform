#pragma once
#define _USE_MATH_DEFINES
#include "Animation.h"
#include <math.h>
#include "DefExport.h"
namespace GameEngine
{
	class DllExport AlphaAnimation : Animation
	{

	public:
		AlphaAnimation() :Animation(MARXAnimatnionType::Alpha)
		{
		}
	};


	class DllExport Back {

	public:
		static float  easeIn(float t, float b, float c, float d) {
			float s = 1.70158f;
			return c*(t /= d)*t*((s + 1)*t - s) + b;
		}

		static float  easeIn(float t, float b, float c, float d, float s) {
			return c*(t /= d)*t*((s + 1)*t - s) + b;
		}

		static float  easeOut(float t, float b, float c, float d) {
			float s = 1.70158f;
			return c*((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
		}

		static float  easeOut(float t, float b, float c, float d, float s) {
			return c*((t = t / d - 1)*t*((s + 1)*t + s) + 1) + b;
		}

		static float  easeInOut(float t, float b, float c, float d) {
			float s = 1.70158f;
			if ((t /= d / 2) < 1) return c / 2 * (t*t*(((s *= (1.525f)) + 1)*t - s)) + b;
			return c / 2 * ((t -= 2)*t*(((s *= (1.525f)) + 1)*t + s) + 2) + b;
		}

		static float  easeInOut(float t, float b, float c, float d, float s) {
			if ((t /= d / 2) < 1) return c / 2 * (t*t*(((s *= (1.525f)) + 1)*t - s)) + b;
			return c / 2 * ((t -= 2)*t*(((s *= (1.525f)) + 1)*t + s) + 2) + b;
		}

	};

	class DllExport Bounce {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			return c - easeOut(d - t, 0, c, d) + b;
		}
		static float  easeOut(float t, float b, float c, float d) {
			if ((t /= d) < (1 / 2.75f)) {
				return c*(7.5625f*t*t) + b;
			}
			else if (t < (2 / 2.75f)) {
				return c*(7.5625f*(t -= (1.5f / 2.75f))*t + .75f) + b;
			}
			else if (t < (2.5 / 2.75)) {
				return c*(7.5625f*(t -= (2.25f / 2.75f))*t + .9375f) + b;
			}
			else {
				return c*(7.5625f*(t -= (2.625f / 2.75f))*t + .984375f) + b;
			}
		}
		static float  easeInOut(float t, float b, float c, float d) {
			if (t < d / 2) return easeIn(t * 2, 0, c, d) * .5f + b;
			else return easeOut(t * 2 - d, 0, c, d) * .5f + c*.5f + b;
		}
	};

	class DllExport Circ {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			return -c * ((float)sqrt(1 - (t /= d)*t) - 1) + b;
		}
		static float  easeOut(float t, float b, float c, float d) {
			return c * (float)sqrt(1 - (t = t / d - 1)*t) + b;
		}
		static float  easeInOut(float t, float b, float c, float d) {
			if ((t /= d / 2) < 1) return -c / 2 * ((float)sqrt(1 - t*t) - 1) + b;
			return c / 2 * ((float)sqrt(1 - (t -= 2)*t) + 1) + b;
		}
	};

	class DllExport Cubic {
	public:
		static float easeIn(float t, float b, float c, float d) {
			return c*(t /= d)*t*t + b;
		}

		static float easeOut(float t, float b, float c, float d) {
			return c*((t = t / d - 1)*t*t + 1) + b;
		}

		static float easeInOut(float t, float b, float c, float d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t + b;
			return c / 2 * ((t -= 2)*t*t + 2) + b;
		}
	};


	class DllExport Elastic {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;
			float p = d*.3f;
			float a = c;
			float s = p / 4;
			return -(a*(float)pow(2, 10 * (t -= 1)) * (float)sin((t*d - s)*(2 * (float)M_PI) / p)) + b;
		}

		static float  easeIn(float t, float b, float c, float d, float a, float p) {
			float s;
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;
			if (a < abs(c)) { a = c;  s = p / 4; }
			else { s = p / (2 * (float)M_PI) * (float)asin(c / a); }
			return -(a*(float)pow(2, 10 * (t -= 1)) * (float)sin((t*d - s)*(2 * M_PI) / p)) + b;
		}

		static float  easeOut(float t, float b, float c, float d) {
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;
			float p = d*.3f;
			float a = c;
			float s = p / 4;
			return (a*(float)pow(2, -10 * t) * (float)sin((t*d - s)*(2 * (float)M_PI) / p) + c + b);
		}

		static float  easeOut(float t, float b, float c, float d, float a, float p) {
			float s;
			if (t == 0) return b;  if ((t /= d) == 1) return b + c;
			if (a < abs(c)) { a = c;  s = p / 4; }
			else { s = p / (2 * (float)M_PI) * (float)asin(c / a); }
			return (a*(float)pow(2, -10 * t) * (float)sin((t*d - s)*(2 * (float)M_PI) / p) + c + b);
		}

		static float  easeInOut(float t, float b, float c, float d) {
			if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
			float p = d*(.3f*1.5f);
			float a = c;
			float s = p / 4;
			if (t < 1) return -.5f*(a*(float)pow(2, 10 * (t -= 1)) * (float)sin((t*d - s)*(2 * (float)M_PI) / p)) + b;
			return a*(float)pow(2, -10 * (t -= 1)) * (float)sin((t*d - s)*(2 * (float)M_PI) / p)*.5f + c + b;
		}

		static float  easeInOut(float t, float b, float c, float d, float a, float p) {
			float s;
			if (t == 0) return b;  if ((t /= d / 2) == 2) return b + c;
			if (a < abs(c)) { a = c; s = p / 4; }
			else { s = p / (2 * (float)M_PI) * (float)asin(c / a); }
			if (t < 1) return -.5f*(a*(float)pow(2, 10 * (t -= 1)) * (float)sin((t*d - s)*(2 * (float)M_PI) / p)) + b;
			return a*(float)pow(2, -10 * (t -= 1)) * (float)sin((t*d - s)*(2 * (float)M_PI) / p)*.5f + c + b;
		}

	};

	class DllExport Expo {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			return (t == 0) ? b : c * (float)pow(2, 10 * (t / d - 1)) + b;
		}

		static float  easeOut(float t, float b, float c, float d) {
			return (t == d) ? b + c : c * (-(float)pow(2, -10 * t / d) + 1) + b;
		}

		static float  easeInOut(float t, float b, float c, float d) {
			if (t == 0) return b;
			if (t == d) return b + c;
			if ((t /= d / 2) < 1) return c / 2 * (float)pow(2, 10 * (t - 1)) + b;
			return c / 2 * (-(float)pow(2, -10 * --t) + 2) + b;
		}

	};

	class DllExport Linear {
	public:
		static float easeNone(float t, float b, float c, float d) {
			return c*t / d + b;
		}

		static float easeIn(float t, float b, float c, float d) {
			return c*t / d + b;
		}

		static float easeOut(float t, float b, float c, float d) {
			return c*t / d + b;
		}

		static float easeInOut(float t, float b, float c, float d) {
			return c*t / d + b;
		}

	};

	class DllExport PositionXAnimation : Animation {

	public:
		PositionXAnimation() :Animation(MARXAnimatnionType::PositionX)
		{

		}
	};

	class DllExport PositionYAnimation : Animation {

	public:
		PositionYAnimation() :Animation(MARXAnimatnionType::PositionY)
		{

		}
	};
	class DllExport Quad {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			return c*(t /= d)*t + b;
		}

		static float  easeOut(float t, float b, float c, float d) {
			return -c *(t /= d)*(t - 2) + b;
		}

		static float  easeInOut(float t, float b, float c, float d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t + b;
			return -c / 2 * ((--t)*(t - 2) - 1) + b;
		}
	};

	class DllExport Quart {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			return c*(t /= d)*t*t*t + b;
		}

		static float  easeOut(float t, float b, float c, float d) {
			return -c * ((t = t / d - 1)*t*t*t - 1) + b;
		}

		static float  easeInOut(float t, float b, float c, float d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t*t + b;
			return -c / 2 * ((t -= 2)*t*t*t - 2) + b;
		}
	};

	class DllExport Quint {
	public:
		static float easeIn(float t, float b, float c, float d) {
			return c*(t /= d)*t*t*t*t + b;
		}

		static float easeOut(float t, float b, float c, float d) {
			return c*((t = t / d - 1)*t*t*t*t + 1) + b;
		}
		static float easeInOut(float t, float b, float c, float d) {
			if ((t /= d / 2) < 1) return c / 2 * t*t*t*t*t + b;
			return c / 2 * ((t -= 2)*t*t*t*t + 2) + b;
		}

	};

	class DllExport RotationAnimation : Animation {

	public:
		RotationAnimation() :Animation(MARXAnimatnionType::Rotate)
		{

		}
	};

	class DllExport ScaleXAnimation : Animation {

	public:
		ScaleXAnimation() :Animation(MARXAnimatnionType::ScaleX)
		{

		}
	};


	class DllExport ScaleXYAnimation : Animation {

	public:
		ScaleXYAnimation() :Animation(MARXAnimatnionType::ScaleXY)
		{

		}
	};


	class DllExport ScaleYAnimation : Animation {

	public:
		ScaleYAnimation() :Animation(MARXAnimatnionType::ScaleY)
		{

		}
	};
	class DllExport Sine {
	public:
		static float  easeIn(float t, float b, float c, float d) {
			return -c * (float)cos(t / d * (M_PI / 2)) + c + b;
		}

		static float  easeOut(float t, float b, float c, float d) {
			return c * (float)sin(t / d * (M_PI / 2)) + b;
		}

		static float  easeInOut(float t, float b, float c, float d) {
			return -c / 2 * ((float)cos(M_PI*t / d) - 1) + b;
		}

	};

	class DllExport TranslateXAnimation : Animation {

	public:
		TranslateXAnimation() :Animation(MARXAnimatnionType::TranslateX)
		{

		}
	};

	class DllExport TranslateYAnimation : Animation {

	public:
		TranslateYAnimation() :Animation(MARXAnimatnionType::TranslateY)
		{

		}
	};
}