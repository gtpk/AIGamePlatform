#include "GameObejct.h"
#include "ObjectManager.h"


GameObejct::GameObejct(GameObejct_TYP_ENUM type)
	: m_name("") , objtype(type)
{
	m_ObjectManager = ObjectManager::GetInstance();
	m_ObjectManager->ObjectdefaultName(this);
}


GameObejct::~GameObejct(void)
{
	m_ObjectManager->DeleteGameObejct(m_name);
	VEC_ATTACH::iterator _itor = m_AttachChild.begin();
	while (_itor != m_AttachChild.end())
	{
		AttacheAble* obj = *_itor;
		_itor = m_AttachChild.erase(_itor);
		delete(obj);
	}
}

bool GameObejct::OnAttech(AttacheAble* _pattachable)
{
	if(_pattachable == NULL)
		return false;

	m_AttachChild.push_back(_pattachable);
	_pattachable->OnAttach(this);

}

const char* GameObejct::is_test(const char* _name)
{
	return m_name.c_str(); 
}