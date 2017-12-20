#include "pacmenplayer.h"

void pacmenplayer::SetType(pacmenStatus type)
{
	if (m_pacmenType == type)
		return;
	m_pacmenType = type;
	KingTimer = 0;
	King_SpriteValue = 0;
	KingRunTimer = 0;
	pacmen_spriteValue = 1;
	onUpdate(50);
}
pacmenStatus pacmenplayer::GetType()
{
	return m_pacmenType;
}

pacmenplayer::pacmenplayer() :ImageControl()
{


	packmendirection[0][0] = "pacmen30";
	packmendirection[0][1] = "pacmen32";
	packmendirection[0][2] = "pacmen70";
	packmendirection[0][3] = "pacmen32";

	packmendirection[1][0] = "pacmen31";
	packmendirection[1][1] = "pacmen33";
	packmendirection[1][2] = "pacmen70";
	packmendirection[1][3] = "pacmen33";

	packmendirection[2][0] = "pacmen34";
	packmendirection[2][1] = "pacmen36";
	packmendirection[2][2] = "pacmen70";
	packmendirection[2][3] = "pacmen36";

	packmendirection[3][0] = "pacmen35";
	packmendirection[3][1] = "pacmen37";
	packmendirection[3][2] = "pacmen70";
	packmendirection[3][3] = "pacmen37";

	for (int i = 0; i < 12; i++)
	{
		char buff[101];
		snprintf(buff, sizeof(buff), "pacmen%02d", 70 + i);
		string kingsrc = buff;
		pacmendie[i] = kingsrc;
	}

	//mb_run_00
	SetType(pacmenStatus::Right);
	setbeckgroundImage(packmendirection[3][3]);
}


void pacmenplayer::SetMoveingSpeedDuration(long duration)
{
	SetAnimationDuration(duration);
}

void pacmenplayer::onUpdate(long long dt)
{
	if (KingTimer < 0)
		KingTimer = 0;

	if (IsDie == true)
		return;
	if (m_pacmenType == pacmenStatus::stop)
	{
		return;
	}

	if (m_pacmenType == pacmenStatus::Left ||
		m_pacmenType == pacmenStatus::Right ||
		m_pacmenType == pacmenStatus::Down ||
		m_pacmenType == pacmenStatus::Up)
	{
		KingTimer += dt;

		if (KingTimer > 50)
		{
			if (King_SpriteValue > King_targetEndValue)
				King_SpriteValue = 0;

			setbeckgroundImage(packmendirection[m_pacmenType][King_SpriteValue]);

			King_SpriteValue++;
			KingTimer = 0;
		}
	}
	else if (m_pacmenType == pacmenStatus::die)
	{
		KingTimer += dt;

		if (KingTimer > 120)
		{
			if (pacmen_spriteValue > pacmen_dietEndValue)
				pacmen_spriteValue = Momo_tragetStartValue;

			setbeckgroundImage(pacmendie[pacmen_spriteValue]);

			pacmen_spriteValue++;

			KingTimer = 0;
		}
	}

}