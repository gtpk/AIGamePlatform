#include "AnimatinonBase.h"

using namespace std;
using namespace GameEngine;

namespace GameEngine
{
	bool AnimationBase::AnimationisEnded()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			if (contator->isEnded() == false)
				return false;
			iter++;
		}
		return true;
	}
	void AnimationBase::SetAnimation(GameEngine::Animation* _ani)
	{
		/*
		Iterator<Animation> iter = animation.iterator();
		while(iter.hasNext())
		{
		Animation contator = (Animation)iter.next();

		if( contator.mType == _ani->mType)
		{
		iter.remove();
		//return;
		}
		}
		*/

		animations.push_back(_ani);
	}

	void AnimationBase::RemoveAnimation(MARXAnimatnionType _aniType)
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;

			if (contator->mType == _aniType)
			{
				delete contator;
				iter = animations.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void AnimationBase::AnimationPlay()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			contator->Play();
			iter++;
		}
	}

	void AnimationBase::AnimationPause()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			contator->Pause();
			iter++;
		}
	}

	void AnimationBase::AnimationRemoveAll()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			delete contator;
			iter = animations.erase(iter);
		}
	}


	void AnimationBase::SetAnimationDuration(long duration)
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			contator->mDuration = duration;
			iter++;
		}
	}

	Animation* AnimationBase::CreateTranslateYAnimation(float StartValue, float EndValue, long Duration)
	{
		Animation* animation = (Animation*)new PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = AnimationType::LinearEaseIn;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		return (Animation*)animation;
	}

	Animation* AnimationBase::CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, bool reverse)
	{
		Animation* animation = (Animation*)new PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = AnimationType::LinearEaseIn;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = reverse;
		return animation;
	}

	Animation* AnimationBase::CreateAlphaAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new AlphaAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		return animation;
	}

	Animation* AnimationBase::CreateAlphaAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* animation = (Animation*)new  AlphaAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mDelay = Delay;
		animation->mRepeat = false;
		return animation;
	}

	Animation* AnimationBase::CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->Play();
		return animation;
	}

	Animation* AnimationBase::CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->mDelay = Delay;
		animation->Play();
		return animation;
	}

	Animation* AnimationBase::CreateTranslateXAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionXAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->Play();
		return animation;
	}

	Animation* AnimationBase::CreateTranslateXAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionXAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->mDelay = Delay;
		animation->Play();
		return animation;
	}

	Animation* AnimationBase::CreateScaleXAnimation(float StartValue, float EndValue, long Duration)
	{
		Animation* _animation = (Animation*)new  ScaleXAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}

	Animation* AnimationBase::CreateScaleXAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->m_AniType = ani;
		_animation->Play();
		return _animation;
	}

	Animation* AnimationBase::CreateScaleXAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->m_AniType = ani;
		_animation->mDelay = Delay;
		_animation->Play();
		return _animation;
	}

	Animation* AnimationBase::CreateScaleYAnimation(float StartValue, float EndValue, long Duration)
	{
		Animation* _animation = (Animation*)new  ScaleYAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}

	Animation* AnimationBase::CreateRotationAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new  RotationAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		return animation;
	}

	Animation* AnimationBase::CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, bool mRepeat, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXYAnimation();
		_animation->mDuration = Duration;
		_animation->m_AniType = ani;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = mRepeat;
		_animation->Play();
		return _animation;
	}


	Animation* AnimationBase::CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXYAnimation();
		_animation->mDuration = Duration;
		_animation->m_AniType = ani;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}

	Animation* AnimationBase::CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXYAnimation();
		_animation->mDuration = Duration;
		_animation->m_AniType = ani;
		_animation->mSaveStartTime = system_clock::now().time_since_epoch().count() / 100000;
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mDelay = Delay;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}

}