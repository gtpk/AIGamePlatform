#include "ImageControl.h"


#ifndef PACMENPLAYER_H
#define PACMENPLAYER_H


enum pacmenStatus
{
	Left  = 0 ,
	Up = 1,
	Right = 2,
	Down = 3,
	die,
	stop
};


class pacmenplayer : public ImageControl
{
public:


	long long KingTimer = 0;
	long long  King_targetEndValue = 3;
	long long  King_SpriteValue = 0;

	long long KingRunTimer = 0;
	long long  pacmen_dietEndValue = 12;
	long long  Momo_tragetStartValue = 1;
	long long  pacmen_spriteValue = 0;

	//private ImageControl King;

private:

public:
	bool IsDie = false;

	bool IsEnable = true;


	string packmendirection[4][4];
	string pacmendie[12];


	pacmenStatus m_pacmenType;
	void SetType(pacmenStatus type);
	pacmenStatus GetType();
	int targetid = 0;
public:
	pacmenplayer();

	void SetMoveingSpeedDuration(long duration);


public:



private:
	long long AnimationDuration = 0;

public:
	void onUpdate(long long dt);

};
#endif // DEBUG