#include "GameStadiumScreen.h"

namespace GameEngine
{
	GameStadiumScreen::GameStadiumScreen()
	{
		ElpseTimer = 0;
		_SelectID = -1;
		m_isPressd = false;
	}

	void GameStadiumScreen::onDrawFrame()
	{
		glPushMatrix();

		//glOrtho(0, 480, 0, 800, -1.0f, 1.0f);

		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		long long dt = ms.count() - ElpseTimer;
		if (dt < 0)
			dt = 0;
		ElpseTimer = ms.count();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


		StageManager::GetGameGraphic()->GetGameStage()->onUpdate(dt);

		glRasterPos2i(0, 0);
		//glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
		glLoadIdentity();
		Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

		glScaled((float)(GameSize.x / 1264.0f), (float)(GameSize.y / 682.0f), 1);
		//m_quad->draw();
		StageManager::GetGameGraphic()->GetGameStage()->onDrawScreen();
		glPopMatrix();
	}
	int GameStadiumScreen::glPrintf(const char *format, ...)
	{
		char buffer[1024];
		std::va_list arg;
		int ret = 0;
		return ret;
	}

	void GameStadiumScreen::onSurfaceChanged(int width, int height)
	{

		//TODO Auto-generated method stub
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//GLU.gluPerspective(gl, 45.0f, (float) width / height, -20.0f, 30.0f);
		//gluOrtho2D( 0, 480, 800, 0);
		glOrtho(0,
			width,
			0,
			height,
			-1, 10000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Point GameSize;
		GameSize.x = width;
		GameSize.y = height;
		ExGameGraphicInfo::GetGameGraphic()->SetGameSize(GameSize);

	}

	void GameStadiumScreen::onSurfaceCreated()
	{

		// TODO Auto-generated method stub

		//m_quad.InitTexture(gl, ExGameInfo.GetGameInfo().GetContext());
		//glClearColor(0.87f, 0.87f, 0.87f, 0.0f);										// RGBA
		glEnable(GL_TEXTURE_2D);									// 텍스쳐 활성
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);	// ??	

												//gl.glEnable(GL_LINE_SMOOTH);
												//gl.glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
		KardNameFactory::GetKardNameFactory()->OneTimeInit();

		ElpseTimer = system_clock::now().time_since_epoch().count() / 100000;
	}

	bool GameStadiumScreen::onTouchEvent(MotionEvent _event)
	{

		bool isPressd = false;
		switch (_event.state) {
		case GLUT_DOWN:
			isPressd = true;
			break;
		case GLUT_UP:
			isPressd = false;
			break;
		}
		if (isPressd == m_isPressd)
		{
			return true;
		}
		else
		{
			m_isPressd = isPressd;
			StageManager::GetGameGraphic()->GetGameStage()->onTouchEvent(_event);
		}
		return true;
	}

	void GameStadiumScreen::XboxControllerKeyEvent(WORD Button, bool Updown)
	{
		StageManager::GetGameGraphic()->GetGameStage()->XboxControllerKeyEvent(Button, Updown);
	}

	void GameStadiumScreen::deleteSelectPiece()
	{

		StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child;
		std::vector<ImageControl*>::iterator _itor = StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child.begin();

		while (_itor != StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child.end())
		{
			ImageControl* target = *_itor;
			if (target != NULL)
			{
				if (target->_currentName == _SelectID)
				{
					delete(target);
					_itor = StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child.erase(_itor);
				}
				else
				{
					target->deleteSelectPiece(_SelectID);
					_itor++;
				}
			}

		}
	}
}