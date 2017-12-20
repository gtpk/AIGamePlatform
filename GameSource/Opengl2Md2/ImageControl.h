#pragma once
#include <Windows.h>
#include <stdio.h>
#if _MSC_VER < 1900 
#define snprintf _snprintf
#endif
#include <string>
#include <vector>
#include "UIBase.h"
#include "IEventHandler.h"
#include "Animation.h"
#include "ClickEventArgs.h"
#include "defAnimations.h"
#include "AnimatinonBase.h"
#include "GameWorld.h"
#include "DefExport.h"

using namespace std;

namespace GameEngine
{
	class DllExport ImageControl :
		public UIBase,
		public IEventHandler<ClickEventArgs>,
		public SelectableObject,
		public AnimationBase
	{
	public:
		GLfloat vertexBuffer[15];
		float uv_x;
		float uv_y;
		GLfloat textureBuffer[15];

		unsigned short index[6];

		string Name;
		int _currentName;
		int NowTextureId;

		bool isWidthPercent;
		bool isHeightPercent;

		bool NotExsistImage;
		int Aligen;

		float zindex;
		float m_rotate;

		bool IsVerticalReverse;

		float ScaleX;
		float ScaleY;

		int transparent;

		string TextureName ;

		bool isIsVerticalReverse();

		void setIsVerticalReverse(bool isVerticalReverse);

	public:
		vector<ImageControl*> m_Child;

	public:

	public:
		void addChild(ImageControl* child);

		virtual vector<ImageControl*> getAllChild();

		virtual void Load(ImageControl* mother, TiXmlNode * MapPieces);
		

		virtual void Save(TiXmlElement * MapPieces);


		COMMONDATATYPE::Vector3d GetNowPostion();
		void SetNowPostion(COMMONDATATYPE::Vector3d pos);

	public:
		// Note! 리스트에서만 지워진다. 객체는 지우지 않는다!
		void Remove(ImageControl* child);

	public:
		bool AllAnimationFinished();

	public:

		/////////////////////////////////////////////////////////////////
		/*  UIBase를 구현하기위하여 사용하는 변수들                                                    */
		/////////////////////////////////////////////////////////////////



		/////////////////////////////////////////////////////////////////

		
		ImageControl();
		ImageControl(string ObjName);
		ImageControl(string ObjName, float width, float height);
		~ImageControl();

		bool OntimeInit = false;

		virtual void SetWidth(float width); //@Override

		virtual void SetHeight(float height); //@Override

		static ImageControl* Load(TiXmlNode * MapPieces);


		static ImageControl* CreateImageControl(string objectName,
			string ImageName, int x, int y);

		static ImageControl* CreateImageControl(string objectName,
			string ImageName, int x, int y, int width, int height);
		static ImageControl* CreateImageControl(ImageControl* target);

		static ImageControl* CreateImageControl(ImageControl* target, string objectName,
			string ImageName, int x, int y, int width, int height);

		static ImageControl* CreateImageControl(ImageControl* target, string objectName,
			string ImageName, int x, int y);

		virtual void eventReceived(UIBase* sender, ClickEventArgs e) { }

		void OnDraw(bool isSelect = false);

		void setbeckgroundImage(string string);

		void setbeckgroundImage(string string, float width, float height);
	};
}