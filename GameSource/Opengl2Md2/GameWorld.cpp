/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Md2Player.cpp -- Copyright (c) 2006 David Henry
// last modification: feb. 25, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Implementation of MD2 Player class.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>

#else
#include "dirent.h"
#endif


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>

#include "Opengl2md2.h"

#include "GameWorld.h"
#include "Md2Object.h"

#include "Texture.h"
#include "PieceModel.h"
#include "../Common/VolkesInterface.h"
#include "ProjectLoader.h"
#include "LuaScriptAttached.h"
#include "ObjectNumberingMananger.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "ViewCamera.h"
//#include "Opengl2md2.h"


using std::cout;
using std::cerr;
using std::endl;
using namespace GameEngine;
/////////////////////////////////////////////////////////////////////////////
//
// class Md2Player implementation.
//
/////////////////////////////////////////////////////////////////////////////

// static 초기화는 이렇게 이루어지는것!
GameWorld *GameWorld::inst = NULL;

// --------------------------------------------------------------------------
// Md2Player::Md2Player
//
// Constructor.  Read a MD2 player from directory.
// --------------------------------------------------------------------------

GameWorld::GameWorld()
throw (std::runtime_error)
	:  MAX_PIECE(20), _Bottompos(99), SelectableObject()
{
	_RootDirctory = ProjectLoader::getinstance()->GetProjectPath();

	GameWorld::inst = this;

	ObjectManager* m_ObjectManager = ObjectManager::GetInstance();

	Volkes = NULL;
	//Md2Object * obj = setNewPiece("chr_01.md2", "chr_01.tga", ViewCamera::getinstance()->eye);
	//
	//if (obj != NULL)
	//{
	//	//_playerMesh = Md2ModelPtr((Md2Model*)obj->model());
	//	m_ObjectManager->ReplaceGameObejct("MainCharacter", obj);
	//	obj->setScale(0.05);
	//
	//	//3.5 -331 z 는 아무거나
	//	obj->setRotate(3.5, -331, 0);
	//	LuaScriptAttached * attach = new LuaScriptAttached();
	//	obj->OnAttech(attach);
	//}
	//	
	


}



// --------------------------------------------------------------------------
// Md2Player::~Md2Player
//
// Destructor.
// --------------------------------------------------------------------------

GameWorld::~GameWorld ()
{
}



// --------------------------------------------------------------------------
// Md2Player::drawPlayerItp
//
// Draw player objects with interpolation.
// --------------------------------------------------------------------------

void GameWorld::drawPlayerItp (bool animated, Md2Object::Md2RenderMode renderMode)
{
	
	Md2Iter md2begin = child.begin();

	for(; md2begin != child.end();  md2begin++)
	{
		Md2Object* node = (Md2Object*)*md2begin;

		node->drawObjectItp (animated, renderMode);
	}



}


// --------------------------------------------------------------------------
// Md2Player::drawPlayerFrame
//
// Draw player objects at a given frame.
// --------------------------------------------------------------------------

void GameWorld::drawPlayerFrame (int frame, Md2Object::Md2RenderMode renderMode)
{

	Md2Iter md2begin = child.begin();
	Md2Iter md2End = child.end();

	for(; md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		node->drawObjectFrame (frame, renderMode);
	}
	
	
}


// --------------------------------------------------------------------------
// Md2Player::animate
//
// Animate player objects.
// --------------------------------------------------------------------------

void GameWorld::animate (GLfloat percent)
{

	Md2Iter md2begin = child.begin();
	Md2Iter md2End = child.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
	
		if(node->GetName() == "MainCharacter")
		{
			node->animate(percent);
		}
	}

}


// --------------------------------------------------------------------------
// Md2Player::setScale
//
// Scale model objects.
// --------------------------------------------------------------------------

void GameWorld::setScale (GLfloat scale)
{
	Md2Object* obj = (Md2Object*)FindSelectTopObj();
	if (obj != NULL)
	{
		ModelInteface* model = obj->model();
		if (model != NULL)
			model->setScale(scale);
	}
}


// --------------------------------------------------------------------------
// Md2Player::setSkin
//
// Set player skin.
// --------------------------------------------------------------------------

void GameWorld::setSkin (const string &name)
{
	Md2Object* obj = (Md2Object*)FindSelectTopObj();

	if (obj != NULL)
	{
		ModelInteface* model = obj->model();
		if(model != NULL)
			model->setTexture(name);
	}
}


// --------------------------------------------------------------------------
// Md2Player::setAnim
//
// Set current player animation.
// --------------------------------------------------------------------------

void GameWorld::setAnim (const string &name)
{

}

void GameWorld::setRotate(vec3_t angle)
{
	Md2Object* obj = (Md2Object*)FindSelectTopObj();

	if(obj != NULL)
		obj->setRotate(angle);

}

void GameWorld::setTranslate(vec3_t trance )
{

	Md2Object* obj = (Md2Object*)FindSelectTopObj();

	obj->setTranslate(trance);

}




void GameWorld::deleteSelectPiece()
{
	Md2Iter md2begin = child.begin();
	Md2Iter md2End = child.end();
	for(; md2begin != md2End ; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->GetUniqNumber() == ObjectMove::getinstance()->SelectObjectNum[0])
		{
			delete node;
			md2begin = child.erase(md2begin);

			return;
		}
		else
		{
			node->deleteSelectPiece(ObjectMove::getinstance()->SelectObjectNum[0]);
		}
		md2begin++;

	}
}

void GameWorld::setSelectionCopy()
{
	m_copycount = 0;
	this->m_CopyID.clear();
	if (ObjectMove::getinstance()->SelectObjectNum.size() == 0)
		return;
	this->m_CopyID.push_back(ObjectMove::getinstance()->SelectObjectNum[0]);
}

void GameWorld::setSelectionPaste()
{
	m_copycount++;
	Md2Object* node = (Md2Object*)FindSelectTopObj();
	setNewPiece(node);
	
	

}

void GameWorld::duplicateSelectPiece()
{
	Md2Iter md2begin = child.begin();
	Md2Iter md2End = child.end();
	for(; md2begin != md2End ; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->GetUniqNumber() == ObjectMove::getinstance()->SelectObjectNum[0])
		{
			setNewPiece(node);
			return;
		}
		md2begin++;

	}
}




// --------------------------------------------------------------------------
// Md2Player::setNewPiece
//
// 피스 등록하는 함수
// --------------------------------------------------------------------------


Md2Object *GameWorld::setNewPiece(const string &dirname,const string &md2Name,const string &textureName,COMMONDATATYPE::Vector3d eye)
{
	std::ifstream pieceifs;

	string path = dirname + "/" + md2Name;
	pieceifs.open (path.c_str (), std::ios::binary);

	if (!pieceifs.fail ())
	{
		pieceifs.close ();
		return false;
	}

	GLfloat pos = -10;

	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()
	obj->setModel (path,textureName);
	obj->setRotate(0,90,90);
	obj->setTranslate(0,pos,pos/2);
	pos+=2;
	obj->setScale(0.1);
	child.push_back(obj);

	// Set first skin as default skin
	// 피스는 에니메이션이 없다고 가정한다.
	//_currentSkin = Model->skins().begin ()->first;
	//_currentAnim = obj->currentAnim ();
	if(Volkes != NULL)
		Volkes->setNewPiece(obj);
	return obj;
}

Md2Object *GameWorld::setNewPiece(const string &md2Name, const string &textureName, COMMONDATATYPE::Vector3d eye)
{
	std::ifstream pieceifs;

	string path = _RootDirctory + "/" + md2Name;
	pieceifs.open(path.c_str(), std::ios::binary);

	if (!pieceifs.fail())
	{
		pieceifs.close();
		return false;
	}

	GLfloat pos = -10;

	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()
	obj->setModel(path, textureName);
	obj->setRotate(0, 90, 90);
	obj->setTranslate(0, pos, pos / 2);
	pos += 2;
	obj->setScale(0.1);
	child.push_back(obj);

	// Set first skin as default skin
	// 피스는 에니메이션이 없다고 가정한다.
	//_currentSkin = Model->skins().begin ()->first;
	//_currentAnim = obj->currentAnim ();
	Volkes->setNewPiece(obj);
	return obj;
}

Md2Object *GameWorld::setNewPieceChar(const string &md2Name, const string &textureName, COMMONDATATYPE::Vector3d eye)
{
	std::ifstream pieceifs;

	string path = _RootDirctory + "/"+ md2Name;
	pieceifs.open (path.c_str (), std::ios::binary);

	if (pieceifs.fail ())
	{
		return false;
	}
	pieceifs.close ();

	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()
	obj->setModel (md2Name,textureName);
	obj->setRotate(0,90,90);
	obj->setScale(0.025);
	obj->setTranslate(eye.x+5,eye.y+5,0);

	child.push_back(obj);
	if (Volkes != NULL)
		Volkes->setNewPiece(obj);
	return obj;
}

void GameWorld::Refresh()
{
	Md2Iter md2begin = child.begin();
	Md2Iter md2End = child.end();
	for (; md2begin != md2End; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if (Volkes != NULL)
			Volkes->setNewPiece(node);
		node->Refresh();
		md2begin++;

	}
}

Md2Object *GameWorld::setNewPiece(const string &md2Name,const string &textureName,float x,float y,float z)
{
	COMMONDATATYPE::Vector3d data;
	data.x = x;
	data.y = y;
	data.z = z;
	return setNewPiece(md2Name,textureName,data);
}

Md2Object *GameWorld::setNewPiece(float Width,float Height , const string &textureName)
{


	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()
	obj->setModel (Width,Height,textureName);
	obj->setRotate(0,90,90);
	obj->setScale(0.1);

	obj->setTranslate(
		ViewCamera::getinstance()->eye.x,
		ViewCamera::getinstance()->eye.y,
		0);
	//obj->setTranslate(ViewCamera::getinstance()->eye.x,ViewCamera::getinstance()->eye.y,ViewCamera::getinstance()->eye.z);

	
	child.push_back(obj);
	if (Volkes != NULL)
		Volkes->setNewPiece(obj);
	LuaScriptAttached * attach = new LuaScriptAttached();

	obj->OnAttech(attach);
	return obj;
}

void GameWorld::setNewImageControl(const string &textureName)
{
	ImageControl* node= ImageControl::CreateImageControl(textureName, textureName, 0, 0);
	StageManager::GetGameGraphic()->GetGameStage()->addChild(node);
}

void GameWorld::setNewImageControl(ImageControl* model, const string &textureName)
{
	ImageControl::CreateImageControl(model,textureName, textureName, 0, 0);
}

Md2Object *GameWorld::setNewPiece(const string &textureName)
{

	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()
	obj->SetAtlasObj(textureName);
	obj->setRotate(0, 90, 90);
	obj->setScale(0.1);

	obj->setTranslate(
		ViewCamera::getinstance()->eye.x,
		ViewCamera::getinstance()->eye.y,
		0);
	//obj->setTranslate(ViewCamera::getinstance()->eye.x,ViewCamera::getinstance()->eye.y,ViewCamera::getinstance()->eye.z);


	child.push_back(obj);
	Volkes->setNewPiece(obj);
	LuaScriptAttached * attach = new LuaScriptAttached();

	obj->OnAttech(attach);
	return obj;
}

Md2Object *GameWorld::setNewPiece(Md2Object* model)
{
	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()
	
	if (model->model() != NULL)
	{
		Md2Model* md2 = dynamic_cast<Md2Model*>(model->model());
		if (md2 != NULL)
		{
			obj->setModel(model->model());
		}
		else
		{
			PieceModel* piece = dynamic_cast<PieceModel*>(model->model());
			if (piece != NULL)
			{
				obj->setModel(piece->GetPieceWidth(),piece->GetPieceHeight(),
					model->m_textureName, model->m_textureAlpha);
			}
		}
		
	}
	else
		obj->SetAtlasObj(model->m_obj->TextureName);


	obj->setTranslate(
		ViewCamera::getinstance()->eye.x + m_copycount*0.1,
		ViewCamera::getinstance()->eye.y + m_copycount*0.1,
		0);

	
	obj->setRotate(0,90,model->getRotate()[2]);
	model->CopyDeepObj(obj);
	
	child.push_back(obj);
	if (Volkes != NULL)
		Volkes->setNewPiece(obj);
	LuaScriptAttached * attach = new LuaScriptAttached();

	obj->OnAttech(attach);

	return obj;

}
Md2Object *GameWorld::MakePiece(Md2Object* model)
{
	Md2Object* obj = new Md2Object(this);
	//_WorldPiece.push_back()

	if (model->model() != NULL)
		obj->setModel(model->model());
	else
		obj->SetAtlasObj(model->m_obj->TextureName);

	obj->setTranslate(model->getTranslate());
	obj->setRotate(0, 90, model->getRotate()[2]);
	model->CopyDeepObj(obj);
	LuaScriptAttached * attach = new LuaScriptAttached();
	obj->OnAttech(attach);
	return obj;
}

Md2Object *GameWorld::setNewPiece(float Width,float Height, const string &textureName,const string &textureAlpha, bool isAbsolute)
{

	
	Md2Object* obj = new Md2Object(this);
	obj->setModel (Width,Height,textureName,textureAlpha, isAbsolute);
	obj->setRotate(0,90,90);
	obj->setScale(0.1);
	obj->setTranslate(
		Width/2,
		Height/2,
		0);

	
	child.push_back(obj);
	if (Volkes != NULL)
		Volkes->setNewPiece(obj);
	LuaScriptAttached * attach = new LuaScriptAttached();

	obj->OnAttech(attach);


	return obj;
}

Md2Object *GameWorld::setNewPiece(Md2Object* model, float Width, float Height, const string &textureName, const string &textureAlpha)
{

	Md2Object* obj = new Md2Object(this);
	obj->setModel(Width, Height, textureName, textureAlpha);
	obj->setRotate(0, 90, 90);
	obj->setScale(0.1);
	obj->setTranslate(
		ViewCamera::getinstance()->eye.x,
		ViewCamera::getinstance()->eye.y,
		0);
	// 알리기
	if (Volkes != NULL)
		Volkes->setNewPiece(model,obj);

	LuaScriptAttached * attach = new LuaScriptAttached();
	obj->OnAttech(attach);
	model->setNewPiece(obj);
	return obj;
}


void GameWorld::CreateSet()
{
	TiXmlDocument doc;
	TiXmlElement* msg;

	//문서 설정
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");

	doc.LinkEndChild(decl);
	// Root 만들자
	TiXmlElement * root = new TiXmlElement("MinMonstersMap");
	doc.LinkEndChild(root);

	root->SetAttribute("name", "Example");
	root->SetAttribute("RootFolder", _RootDirctory.c_str());

	//경고 문구삽입
	//TiXmlComment * comment = new TiXmlComment();
	//comment->SetValue("자동 완성된 코드 이므로 직접 수정 하지 마시오." );  
	//root->LinkEndChild( comment );

	TiXmlElement * MapPieces = new TiXmlElement("MapPieces");
	root->LinkEndChild(MapPieces);

	((Md2Object*)FindSelectTopObj())->Save(MapPieces);

	if (Volkes != NULL)
	{
		doc.SaveFile(Volkes->SaveUrl().c_str());
	}
	
	
}

void GameWorld::Save()
{
	TiXmlDocument doc;  
	TiXmlElement* msg;

	//문서 설정
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	
	doc.LinkEndChild( decl );
	// Root 만들자
	TiXmlElement * root = new TiXmlElement( "MinMonstersMap" );  
	doc.LinkEndChild( root ); 

	root->SetAttribute("RootFolder",_RootDirctory.c_str());

	//경고 문구삽입
	//TiXmlComment * comment = new TiXmlComment();
	//comment->SetValue("자동 완성된 코드 이므로 직접 수정 하지 마시오." );  
	//root->LinkEndChild( comment );

	TiXmlElement * MapPieces = new TiXmlElement( "MapPieces" );  
	root->LinkEndChild( MapPieces );  

	{
		Md2Iter md2begin = child.begin();
		Md2Iter md2End = child.end();

		for(;md2begin != md2End ; md2begin++)
		{
			Md2Object* node = ((Md2Object*)*md2begin);	
			node->Save(MapPieces);

		}	
	}

	if (Volkes != NULL)
	{
		doc.SaveFile(Volkes->SaveUrl().c_str());
	}
}



bool GameWorld::Load(string str)
{
	TiXmlDocument doc(str.c_str());
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		// 파일이 없음..!!
		printf("File Not Found %s\n", str.c_str());
		return false ;
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
	}


	TiXmlDeclaration* declar = doc.ToDeclaration();
	if(declar != NULL)
	{
		if(declar->Version() != "1.0")
		{
			// 버전이 일치 하지 않음
			return false;
		}
	}
	
	TiXmlNode* MapNode;

	MapNode = doc.FirstChild("MinMonstersMap"); 

	TiXmlElement* MinMonstersMap = MapNode->ToElement();
	_RootDirctory = MinMonstersMap->Attribute("RootFolder");

	TiXmlNode * MapPieces = MapNode->FirstChild( "MapPieces" );  

	
	{
		TiXmlNode* Piece = MapPieces->FirstChild("Piece");

		for(; Piece!=NULL ;Piece = Piece->NextSibling())
		{ 
			int name=101;
			GameObejct_TYP_ENUM type;
			float Scale = 0.1;
			float width;
			float height;
		
			TiXmlElement* pelement = Piece->ToElement();

			pelement->Attribute("Name",&name);
			const char* TextureName = pelement->Attribute("TextureName");
			const char* AlphaTexture = pelement->Attribute("AlphaTexture");
			const char* Md2Name = pelement->Attribute("ModelName");
			int i_type = 0;
			pelement->Attribute("GameObejct_TYP_ENUM", &i_type);
			type = (GameObejct_TYP_ENUM)i_type;
			pelement->QueryFloatAttribute("Scale",&Scale);
			pelement->QueryFloatAttribute("Width", &width);
			pelement->QueryFloatAttribute("Height", &height);

			vec3_t m_translate;

			//TiXmlNode* Trancerate = Piece->FirstChild("Trancerate");
			//TiXmlElement* pTracerate = Trancerate->ToElement();
			pelement->QueryFloatAttribute("Tranceratex",&m_translate[0]);
			pelement->QueryFloatAttribute("Tranceratey",&m_translate[1]);
			pelement->QueryFloatAttribute("Tranceratez",&m_translate[2]);

			vec3_t m_rotation;
			//TiXmlNode* Rotation = Piece->FirstChild("Rotation");
			//TiXmlElement* pRotation = Rotation->ToElement();
			pelement->QueryFloatAttribute("Rotationx",&m_rotation[0]);
			pelement->QueryFloatAttribute("Rotationy",&m_rotation[1]);
			pelement->QueryFloatAttribute("Rotationz",&m_rotation[2]);

			if (type == GameObejct_TYP_ENUM::MARX_OBJECT_MD2_MODEL)
			{
				std::ifstream pieceifs;

				string path = Md2Name;
				pieceifs.open(path.c_str(), std::ios::binary);

				if (pieceifs.fail())
				{
					pieceifs.close();
					continue;
				}
				GLfloat pos = -10;

				Md2Object* obj = new Md2Object(this);
				//_WorldPiece.push_back()
				obj->setName(name);
				obj->setModel(path, TextureName);
				obj->setRotate(m_rotation[0], m_rotation[1], m_rotation[2]);
				obj->setTranslate(m_translate[0], m_translate[1], m_translate[2]);
				obj->setScale(Scale);
				child.push_back(obj);
			}
			else if (type == GameObejct_TYP_ENUM::MARX_OBJECT_MD2_OBJECT)
			{
				//GameWorld::getInstance()._RootDirctory
				string TextureName_str = TextureName;
				TextureName_str = TextureName_str.substr(
					string(GameWorld::getInstance()._RootDirctory + "\\asset\\").length(), TextureName_str.length());
				string AlphaTexture_str = AlphaTexture;
				AlphaTexture_str = AlphaTexture_str.substr(
					string(GameWorld::getInstance()._RootDirctory + "\\asset\\").length(), AlphaTexture_str.length());
				printf("%s / %s\n", TextureName_str.c_str(), AlphaTexture_str.c_str());
				Md2Object* obj = setNewPiece(width, height, TextureName_str.c_str(), AlphaTexture_str.c_str());
				obj->setName(name);
				obj->setRotate(m_rotation[0], m_rotation[1], m_rotation[2]);
				obj->setTranslate(m_translate[0], m_translate[1], m_translate[2]);
				obj->setScale(Scale);
				obj->Load(obj,Piece);
			}

			// 모델이 불러졌는지 확인하고 없으면 에러
			

			
		}	
	}
	
	return false;

}