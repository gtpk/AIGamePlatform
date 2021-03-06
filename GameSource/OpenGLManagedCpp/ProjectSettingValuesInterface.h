#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma unmanaged
#include <strsafe.h>
#pragma managed

// Link lib
#pragma comment(lib, "strsafe.lib")

#define UNREF(x) x;

#include "stdio.h"
#include "../Opengl2Md2/Md2Object.h"
#include "../Opengl2Md2/Md2Model.h"
#include "../Common/VolkesInterface.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "../Opengl2Md2/GameWorld.h"

// Exclude rarely used parts of the windows headers
//#define WIN32_LEAN_AND_MEAN
#define PROPERTYDEFINE(TYPE,NAME) private:\
TYPE m_##NAME;\
public:\
property TYPE NAME\
{\
	void set(TYPE n##NAME)\
	{\
		if(m_##NAME != n##NAME)\
		{\
			m_##NAME = n##NAME;\
			OnPropertyChanged(#NAME);\
		}\
	}\
	TYPE get()\
	{\
		return m_##NAME;\
	}\
}



using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;
using namespace System::Windows::Input;
using namespace System::Windows::Media;
using namespace System::Windows::Forms; // We derive from UserControl this time, so this ref is necessary

using namespace System::Windows::Media::Media3D;
using namespace System::ComponentModel;
using namespace System::Xml;
namespace LogicCommon
{

	public ref class ProjectSettingValuesInterface : public INotifyPropertyChanged
	{
	
	private: 
		static ProjectSettingValuesInterface^ instance = nullptr;
		ProjectSettingValuesInterface()
		{
		}



		

		void OnPropertyChanged(String^ info)
		{
			PropertyChanged(this, gcnew PropertyChangedEventArgs(info));
		}

		PROPERTYDEFINE(String^,ProjectPath)
	

	public:


		virtual event PropertyChangedEventHandler^ PropertyChanged;


		static ProjectSettingValuesInterface^ GetInstance()
		{
			if (instance == nullptr)
			{
				instance = gcnew ProjectSettingValuesInterface();
				instance->ProjectPath = String::Empty;
				if (instance->ProjectPath == String::Empty)
				{
					XmlDocument^ xml = gcnew XmlDocument(); // XmlDocument 생성
					xml->Load(AppDomain::CurrentDomain->BaseDirectory + "ProjectProperty.xml");
					XmlNodeList^ xnList = xml->GetElementsByTagName("Project"); //접근할 노드

					for each (XmlNode^ xn in xnList)
					{
						String^ attrVal = xn->Attributes["RootFolder"]->Value;
						instance->ProjectPath = attrVal;
					}
				}
			}
				
			return instance;
		}


	};
}