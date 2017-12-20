#include "StageManager.h"
#include <map>


using namespace GameEngine;
StageManager* StageManager::m_StageManager = NULL;



namespace GameEngine
{
	IGameStage* StageManager::GetGameStage()
	{
		if (KardNameFactory::GetKardNameFactory()->IsReadForGame() == false)
			return m_LoadingScreen;

		if (savedStage != m_NowStage)
		{
			before_savedStage = savedStage;
			savedStage = m_NowStage;
			TempStage = GetGameStage(GetNowStage());
		}
		return TempStage;
	}

	IGameStage* StageManager::GetGameBeforeStage()
	{
		if (KardNameFactory::GetKardNameFactory()->IsReadForGame() == false)
			return m_LoadingScreen;

		if (savedStage != m_NowStage)
		{
			before_savedStage = savedStage;
			savedStage = m_NowStage;
			TempStage = GetGameStage(GetNowStage());
		}
		return TempStage;
	}

	void StageManager::SetGameStage(IGameStage* Scene)
	{
		TempStage = Scene;
		m_NowStage = StaticStage::Chose;
		GetGameStage(StaticStage::Chose)->onShow();
	}

	IGameStage* StageManager::GetGameStage(StaticStage::KADSTAGE stage)
	{
		switch (stage) {
		case StaticStage::LOADING:
			return m_LoadingScreen;
		case StaticStage::Chose:
			return TempStage;
		default:
			break;
		}
		return NULL;
	}

	void StageManager::SetNowStage(StaticStage::KADSTAGE stage)
	{
		GetGameStage(m_NowStage)->onClose();
		m_NowStage = stage;

		GetGameStage(stage)->onShow();
	}

}