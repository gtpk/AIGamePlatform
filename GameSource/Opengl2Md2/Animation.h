#pragma once
#include <chrono>
#include "DefExport.h"
using namespace std::chrono;

namespace GameEngine
{
	DllExport enum MARXAnimatnionType {
		TranslateX, TranslateY,
		PositionX, PositionY, Alpha, ScaleX, ScaleY, ScaleXY, Rotate,
	};

	DllExport enum AnimationType
	{
		LinearleaseNone,
		BackEaseIn,
		BackEaseOut,
		BackEaseInOut,

		BounceEaseIn,
		BounceEaseOut,
		BounceEaseInOut,

		CircEaseIn,
		CircEaseOut,
		CircEaseInOut,

		CubicEaseIn,
		CubicEaseOut,
		CubicEaseInOut,

		ElasticEaseIn,
		ElasticEaseOut,
		ElasticEaseInOut,

		ExpoEaseIn,
		ExpoEaseOut,
		ExpoEaseInOut,

		LinearEaseIn,
		LinearEaseOut,
		LinearEaseInOut,

		QuadEaseIn,
		QuadEaseOut,
		QuadEaseInOut,

		QuartEaseIn,
		QuartEaseOut,
		QuartEaseInOut,

		QuintEaseIn,
		QuintEaseOut,
		QuintEaseInOut,
	};


	class DllExport Animation
	{
	public :

		Animation()
		{
			mDelay = 0;
			mDuration = 0;
			PauseSaved = 0;
			currentValue = 0;
		}

	
		float mStartValue;
		float mEndValue;
		long long mDuration;
		long long mDelay;
		long long mSaveStartTime;
		bool mFinish = false;
		bool mRepeat = false;
		MARXAnimatnionType mType;
		bool isPause = false;
		AnimationType m_AniType;


		void Copy(Animation _ani);

		float easeFunction(float t, float b, float c, float d);

		Animation(MARXAnimatnionType type);



		bool isStarted();

		bool isEnded();

		bool isRepeat();


		long long PauseSaved;
		float currentValue ;
		float getCurrentValue(long long currentTime);
		void Play();
		void Pause();

		void Stop();
	};


}