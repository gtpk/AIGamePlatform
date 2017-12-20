#pragma once
#include "IGameStage.h"
#include "ViewCamera.h"
#include "GameObejct.h"
#include "LuaScriptAttached.h"
#include "Opengl2md2.h"
#include "pacmenplayer.h"


class pacmengame : public GameEngine::IGameStage
{
public:

	long long dt_timesleep = 2000;

public:
	pacmengame();

public:
	pacmenplayer* pacmen;

	char map[31][58];
	ImageControl * viewmap[31][58];
	void onDrawScreen();
	void loadPacmenMap();

	bool collustion();
public:

	void XboxControllerKeyEvent(WORD Button, bool Updown) ;
	void onShow() ;

	void eventReceived( UIBase* sender, ClickEventArgs e) ;

	void onUpdate(long long dt) ;


	void onClose();
	bool isCloseed();
};
