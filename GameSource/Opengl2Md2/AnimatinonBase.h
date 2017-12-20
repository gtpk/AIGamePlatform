#pragma once
#include "Animation.h"
#include "defAnimations.h"
#include <vector>

using namespace std;
using namespace GameEngine;

namespace GameEngine
{
	class DllExport AnimationBase
	{
	public:
		AnimationBase() { };
		~AnimationBase() {  };


	public:

		bool AnimationisEnded();

		vector<GameEngine::Animation*> animations;

		void SetAnimation(GameEngine::Animation* _ani);

		void RemoveAnimation(MARXAnimatnionType _aniType);

		void AnimationPlay();

		void AnimationPause();

		void AnimationRemoveAll();


		void SetAnimationDuration(long duration);

		static Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration);

		static Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, bool reverse);

		static Animation* CreateAlphaAnimation(float StartValue, float EndValue, long Duration, AnimationType ani);

		static Animation* CreateAlphaAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani);

		static Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, AnimationType ani);

		static Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani);

		static Animation* CreateTranslateXAnimation(float StartValue, float EndValue, long Duration, AnimationType ani);

		static Animation* CreateTranslateXAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani);

		static Animation* CreateScaleXAnimation(float StartValue, float EndValue, long Duration);

		static Animation* CreateScaleXAnimation(float StartValue, float EndValue, long Duration, AnimationType ani);

		static Animation* CreateScaleXAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani);

		static Animation* CreateScaleYAnimation(float StartValue, float EndValue, long Duration);

		static Animation* CreateRotationAnimation(float StartValue, float EndValue, long Duration, AnimationType ani);

		static Animation* CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, bool mRepeat, AnimationType ani);

		static Animation* CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, AnimationType ani);

		static Animation* CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani);
	private:

	};

}