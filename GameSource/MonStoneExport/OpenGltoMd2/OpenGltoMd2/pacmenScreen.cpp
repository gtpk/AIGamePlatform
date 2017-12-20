#include "pacmenScreen.h"
#include <string>
#include "Snumber.h"


pacmengame::pacmengame()
{
	addEventHandler(dynamic_cast<IEventHandler<ClickEventArgs>*> (this));
}
void pacmengame::onDrawScreen()
{
	OnDraw(false);
}

void pacmengame::onClose() {
}

bool pacmengame::isCloseed() {
	return true;
}

void pacmengame::loadPacmenMap()
{
	char buff[101] = "\\Asset\\map.txt";
	std::string buffAsStdStr = GameWorld::getInstance()._RootDirctory + buff;
	printf("AtlasOpen %s\n", buffAsStdStr.c_str());
	//FILE* f = fopen(buffAsStdStr.c_str(), "r");
	ifstream inf(buffAsStdStr.c_str());

	for (int i = 0; i < 31; i++)
	{
		string str2;
		std::getline(inf, str2);
		for (int j = 0; j < 29; j++)
		{
			map[30-i][j] = str2[j];
		}
	}

	int size = 12;


	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			viewmap[i][j] = 0;
			if (map[i][j] == '1')
			{
				viewmap[i][j] = ImageControl::CreateImageControl(
					"minipacmen121", "minipacmen121", j*size, i*size);
			}
			else if (map[i][j] == '2')
			{
				viewmap[i][j] = ImageControl::CreateImageControl(
					"minipacmen119", "minipacmen119", j * size, i* size);
			}
			else if (map[i][j] == '3')
			{
				viewmap[i][j] = ImageControl::CreateImageControl(
					"minipacmen159", "minipacmen159", j * size, i * size);
			}
			else if (map[i][j] == '4')
			{
				viewmap[i][j] = ImageControl::CreateImageControl(
					"minipacmen118", "minipacmen118", j * size, i * size);
			}
			else if (map[i][j] == '5')
			{
				viewmap[i][j] = ImageControl::CreateImageControl(
					"minipacmen122", "minipacmen122", j * size, i * size);
			}
			else if (map[i][j] == '6')
			{
				viewmap[i][j] = ImageControl::CreateImageControl(
					"minipacmen123", "minipacmen123", j * size, i * size);
			}
			if (viewmap[i][j] != 0)
			{
				addChild(viewmap[i][j]);
			}
		}
	}

}

bool pacmengame::collustion()
{
	//충돌 감지

	{
		int Celly = floor((pacmen->y + 6.0f) / 12);
		int Cellx = floor((pacmen->x + 6.0f) / 12);

		if (map[Celly][Cellx] != '.' 
			&& map[Celly][Cellx] != '_' 
			&& map[Celly][Cellx] != 'O')
		{
			return true;
		}
	}
	{
		int Celly = ceil((pacmen->y + 6.0f) / 12);
		int Cellx = ceil((pacmen->x + 6.0f) / 12);

		if (map[Celly][Cellx] != '.' && map[Celly][Cellx] != '_'&& map[Celly][Cellx] != 'O')
		{
			return true;
		}
	}
	{
		int Celly = ceil((pacmen->y + 6.0f) / 12);
		int Cellx = floor((pacmen->x + 6.0f) / 12);

		if (map[Celly][Cellx] != '.' && map[Celly][Cellx] != '_'&& map[Celly][Cellx] != 'O')
		{
			return true;
		}
	}
	{
		int Celly = floor((pacmen->y + 6.0f) / 12);
		int Cellx = ceil((pacmen->x + 6.0f) / 12);

		if (map[Celly][Cellx] != '.' && map[Celly][Cellx] != '_'&& map[Celly][Cellx] != 'O')
		{
			return true;
		}
	}
	return false;
}

void pacmengame::onUpdate(long long dt)
{
	if (KardNameFactory::GetKardNameFactory()->IsLoaded == false)
	{
		return;
	}
	dt = 10;
	//키보드 입력
	//키보드 입력
	if ((Opengl2md2::getInstance().keyboard.keymap[VK_RIGHT] == 1))
	{
		pacmen->x += 0.10*dt;
		if (!collustion())
			pacmen->SetType(pacmenStatus::Right);
		pacmen->x -= 0.10*dt;
	}
	else if (Opengl2md2::getInstance().keyboard.keymap[VK_LEFT] == 1)
	{

		pacmen->x -= 0.10*dt;
		if (!collustion())
			pacmen->SetType(pacmenStatus::Left);
		pacmen->x += 0.10*dt;
	}
	else if (Opengl2md2::getInstance().keyboard.keymap[VK_DOWN] == 1)
	{
		pacmen->y -= 0.10*dt;
		if (!collustion())
			pacmen->SetType(pacmenStatus::Down);
		pacmen->y += 0.10*dt;
	}
	else if (Opengl2md2::getInstance().keyboard.keymap[VK_UP] == 1)
	{
		pacmen->y += 0.10*dt;
		if (!collustion())
			pacmen->SetType(pacmenStatus::Up);
		pacmen->y -= 0.10*dt;
	}

	if (pacmen->GetType() == pacmenStatus::Right)
	{
		pacmen->x += 0.10*dt;
		if(collustion())
			pacmen->x -= 0.10*dt;
	}
	else if (pacmen->GetType() == pacmenStatus::Left)
	{
		pacmen->x -= 0.10*dt;
		if (collustion())
			pacmen->x += 0.10*dt;
	}
	else if (pacmen->GetType() == pacmenStatus::Down)
	{
		pacmen->y -= 0.10*dt;
		if (collustion())
			pacmen->y += 0.10*dt;
	}
	else if (pacmen->GetType() == pacmenStatus::Up)
	{
		pacmen->y += 0.10*dt;
		if (collustion())
			pacmen->y -= 0.10*dt;
	}

	if(collustion())
		pacmen->SetType(pacmenStatus::stop);

	

	pacmen->onUpdate(dt);
	//king_obj->onUpdate(dt);
}
void pacmengame::XboxControllerKeyEvent(WORD Button, bool Updown)
{
}
void pacmengame::onShow()
{
	Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

	ViewCamera::getinstance()->eye.x = 0;
	ViewCamera::getinstance()->eye.y = 0;
	ViewCamera::getinstance()->ViewScale = 1;

	pacmen = new pacmenplayer();
	pacmen->SetWidth(24);
	pacmen->SetHeight(24);
	pacmen->isNotClickable = false;
	pacmen->SetType(pacmenStatus::stop);
	addChild(pacmen);
	pacmen->x = 6;
	pacmen->y = 6;
	loadPacmenMap();
}



void pacmengame::eventReceived(UIBase* sender, ClickEventArgs e)
{

}