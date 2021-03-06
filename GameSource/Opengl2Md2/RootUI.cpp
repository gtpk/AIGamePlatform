#include "Penal.h"
#include "RootUI.h"
using namespace GameEngine;
namespace GameEngine
{
	RootUI::RootUI()
	{
		Penal();
	}
	void RootUI::Save()
	{
		TiXmlDocument doc;
		TiXmlElement* msg;

		//문서 설정
		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");

		doc.LinkEndChild(decl);
		// Root 만들자
		TiXmlElement * root = new TiXmlElement("RootUI");
		doc.LinkEndChild(root);


		//경고 문구삽입
		//TiXmlComment * comment = new TiXmlComment();
		//comment->SetValue("자동 완성된 코드 이므로 직접 수정 하지 마시오." );  
		//root->LinkEndChild( comment );

		TiXmlElement * MapPieces = new TiXmlElement("Child");
		root->LinkEndChild(MapPieces);

		{
			std::vector<ImageControl*>::iterator md2begin = m_Container->m_Child.begin();
			std::vector<ImageControl*>::iterator md2End = m_Container->m_Child.end();
			for (; md2begin != md2End; md2begin++)
			{
				ImageControl* node = ((ImageControl*)*md2begin);
				node->Save(MapPieces);
			}
		}

		if (GameWorld::getInstance().Volkes != NULL)
		{
			doc.SaveFile(GameWorld::getInstance().Volkes->SaveUrl().c_str());
		}
	}



	bool RootUI::Load(string str)
	{
		TiXmlDocument doc(str.c_str());
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			// 파일이 없음..!!
			printf("File Not Found %s\n", str.c_str());
			return false;
			//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		}


		TiXmlDeclaration* declar = doc.ToDeclaration();
		if (declar != NULL)
		{
			if (declar->Version() != "1.0")
			{
				// 버전이 일치 하지 않음
				return false;
			}
		}

		TiXmlNode* MapNode;

		MapNode = doc.FirstChild("RootUI");

		TiXmlElement* MinMonstersMap = MapNode->ToElement();

		TiXmlNode * MapPieces = MapNode->FirstChild("Child");


		{
			TiXmlNode* Piece = MapPieces->FirstChild("ImageControl");

			for (; Piece != NULL; Piece = Piece->NextSibling())
			{
				TiXmlElement* pelement = Piece->ToElement();

				const char* _Name = pelement->Attribute("Name");
				const char* _TextureName = pelement->Attribute("TextureName");
				int _transparent = 255;
				pelement->Attribute("transparent", &_transparent);
				float _ScaleX;
				pelement->QueryFloatAttribute("ScaleX", &_ScaleX);
				float _ScaleY;
				pelement->QueryFloatAttribute("ScaleY", &_ScaleY);
				float _x;
				pelement->QueryFloatAttribute("x", &_x);
				float _y;
				pelement->QueryFloatAttribute("y", &_y);
				float _zindex;
				pelement->QueryFloatAttribute("zindex", &_zindex);
				float _m_rotate;
				pelement->QueryFloatAttribute("m_rotate", &_m_rotate);
				float Width;
				pelement->QueryFloatAttribute("Width", &Width);
				float Height;
				pelement->QueryFloatAttribute("Height", &Height);

				ImageControl* child = ImageControl::CreateImageControl(
					string(_TextureName), _Name, _x, _y);
				child->SetWidth(Width);
				child->SetHeight(Height);
				child->zindex = _zindex;
				child->m_rotate = _m_rotate;
				child->ScaleX = _ScaleX;
				child->ScaleY = _ScaleY;
				addChild(child);

				TiXmlNode * MapPieces = pelement->FirstChild("Child");
				child->Load(child, MapPieces);
			}
		}

		return false;

	}

	void RootUI::OnDraw(bool isSelect)
	{
		vector<ImageControl*>::iterator iter = m_Container->m_Child.begin();

		while (iter != m_Container->m_Child.end()) {
			ImageControl* ParentControl = *iter;
			ParentControl->OnDraw();
			iter++;
		}
	}

	void RootUI::addEventHandler(IEventHandler<ClickEventArgs>* handler)
	{
		TouchEvent.push_back(handler);
	}

	void RootUI::onTouchEvent(MotionEvent event)
	{
		ImageControl* targetImage = NULL;
		vector<ImageControl*> cc = m_Container->getAllChild();
		vector<ImageControl*>::iterator iter = cc.begin();

		//buttons[GLUT_LEFT_BUTTON] == GLUT_UP
		while (iter != cc.end()) {
			ImageControl* ParentControl = *iter;

			int action = event.state;

			int PointNum = 0;

			if (ParentControl->isPrang(event, PointNum)) {
				targetImage = ParentControl;
			}

			if (targetImage != NULL) {

				vector<IEventHandler<ClickEventArgs>* >::iterator eventitor = TouchEvent.begin();
				while (eventitor != TouchEvent.end())
				{
					(*eventitor)->eventReceived(targetImage, ClickEventArgs(event));
					eventitor++;
				}
				return;
			}

			iter++;
		}
	}
}