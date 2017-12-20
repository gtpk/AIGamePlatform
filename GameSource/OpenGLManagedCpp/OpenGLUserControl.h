#pragma once

// Exclude rarely used parts of the windows headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Helper.h"
//#include "OpenGL.h"
#pragma comment(lib,"Opengl2Md2.lib")
#include "../Opengl2Md2/Opengl2md2.h"

// To use these, we must add some references...
//	o PresentationFramework (for HwndHost)
//		* PresentationCore
//		* WindowsBase
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;
using namespace System::Windows::Input;
using namespace System::Windows::Media;
using namespace System::Windows::Forms; // We derive from UserControl this time, so this ref is necessary
using namespace System::Runtime::InteropServices;

namespace WPFOpenGLLib 
{
	public ref class OpenGLUserControl : public UserControl
	{
	private:
		HDC						m_hDC;
		HWND					m_hWnd;
		HGLRC					m_hRC;

		float					m_fRotationAngle;
		
		System::ComponentModel::Container^ components;
	
	public:
		virtual ~OpenGLUserControl()
		{
			if(NULL != m_hRC)
			{
				wglDeleteContext(m_hRC);
				m_hRC = NULL;
			}

			if(NULL != m_hWnd && NULL != m_hDC)
			{
				ReleaseDC(m_hWnd, m_hDC);
				m_hDC = NULL;
			}

			// Don't destroy the HWND... we didn't allocate it!

			if (components) 
			{
				delete components;
			}
		}

		OpenGLUserControl() : components(nullptr),
			m_hDC(NULL),
			m_hWnd(NULL),
			m_hRC(NULL),
			m_fRotationAngle(0.0f)
		{
			InitializeComponent();
			this->components = gcnew System::ComponentModel::Container();

			//Attach load and size change event handlers
			this->Load += gcnew System::EventHandler(this, &OpenGLUserControl::InitializeOpenGL);
			this->SizeChanged += gcnew EventHandler(this, &OpenGLUserControl::ResizeOpenGL);
			//this->KeyDown += gcnew System::EventArgs(&OpenGLUserControl::KeyDown);
		}

	protected:
		void InitializeComponent()
		{
			this->Name = "OpenGLUserControl";
		}

		virtual void OnPaintBackground( PaintEventArgs^ e ) override
		{ 
			UNREF(e);
			// not doing anything here avoids flicker
		}

		virtual void OnPaint( System::Windows::Forms::PaintEventArgs^ e ) override
		{
			UNREF(e);

			if(m_hDC == NULL || m_hRC == NULL)
				return;
			Opengl2md2::getInstance().idleVisible();
			wglMakeCurrent(m_hDC, m_hRC);

				Opengl2md2::getInstance().display();

			SwapBuffers(m_hDC); // NOTE: This is no longer wglSwapBuffers
			//ValidateRect(m_hWnd,NULL);
			/*
			wglMakeCurrent(m_hDC, m_hRC);

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			glTranslatef (0.0f, 0.0f, -2.6f);

			glRotatef(m_fRotationAngle, 0.0f, 1.0f, 0.0f);

			glBegin (GL_TRIANGLES);
				glColor3f (1.0f, 0.0f, 0.0f);	glVertex3f(-1.0f,-1.0f, 0.0f);
				glColor3f (0.0f, 1.0f, 0.0f);	glVertex3f( 0.0f, 1.0f, 0.0f);
				glColor3f (0.0f, 0.0f, 1.0f);	glVertex3f( 1.0f,-1.0f, 0.0f);
			glEnd ();

			glFlush ();
			SwapBuffers(m_hDC); // NOTE: This is no longer wglSwapBuffers

			m_fRotationAngle += 1.0f;
			*/
		}

		/// <summary>
		///	Event handler called when the form is loaded.  It retrieves the controls
		///	window handle and device context and creates the rendering context.
		/// </summary>
		virtual void InitializeOpenGL( Object^ sender, EventArgs^ e)
		{
			UNREF(e);
			UNREF(sender);

			// Get the HWND from the base object
			m_hWnd	= (HWND) this->Handle.ToPointer();

			if(m_hWnd)
			{
				m_hDC = GetDC(m_hWnd);
				if(!m_hDC)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				//
				// Create PixelFormatDescriptor and choose pixel format
				//
				uint PixelFormat;

				BYTE iAlphaBits = 0;
				BYTE iColorBits = 32;
				BYTE iDepthBits = 16;
				BYTE iAccumBits = 0;
				BYTE iStencilBits = 0;

				static PIXELFORMATDESCRIPTOR pfd = 
				{
					sizeof(PIXELFORMATDESCRIPTOR),	//size
					1,								//version
					PFD_DRAW_TO_WINDOW|				//flags
					PFD_SUPPORT_OPENGL|
					PFD_DOUBLEBUFFER,
					PFD_TYPE_RGBA,					//pixeltype
					iColorBits,
					0, 0, 0, 0, 0, 0,				//color bits ignored
					iAlphaBits,						
					0,								//alpha shift ignored
					iAccumBits,						//accum. buffer
					0, 0, 0, 0,						//accum bits ignored
					iDepthBits,						//depth buffer
					iStencilBits,					//stencil buffer
					0,								//aux buffer
					PFD_MAIN_PLANE,					//layer type
					0,								//reserved
					0, 0, 0							//masks ignored
				};
				
				PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
				if(!PixelFormat)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				if(!SetPixelFormat(m_hDC, PixelFormat, &pfd))
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				m_hRC = wglCreateContext(m_hDC);
				if(!m_hRC)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				if(!wglMakeCurrent(m_hDC, m_hRC))
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				//
				// DPI scaling is performed automatically!
				// TODO: Check with non-XP-Style DPI scaling!

				//ShowWindow(m_hWnd, SW_SHOW);
				//SetFocus(m_hWnd);

				//glEnable(GL_DEPTH_TEST);
				//glDisable(GL_TEXTURE_2D);

				if(m_hDC && m_hWnd)
				{
					int argc = 2;
					char str1[] = {"WPFOpenGLApp.exe"};
					char str2[] = {"C:\monstone\GameResource\hueteotl" };
					char *strs[] = {str1,str2};
					char **argv = strs;
					

					Opengl2md2::getInstance().Openflmd2init(argc,argv,m_hDC, m_hRC, m_hWnd);
				}

				return;
			}
		}

		/// <summary>
		/// Event handler called when the control is resized.
		/// </summary>
		void ResizeOpenGL(Object^ sender, EventArgs^ e)
		{
			UNREF(e);
			UNREF(sender);

			if(m_hDC == NULL || m_hRC == NULL)
				return;

			if(Width == 0 || Height == 0)
				return;

			/*
			wglMakeCurrent(m_hDC, m_hRC);
			glViewport( 0, 0, Width, Height );

			glMatrixMode ( GL_PROJECTION );
			glLoadIdentity();
			// gluPerspective( 67.5,((double)(Width) / (double)(Height)), 1.0, 500.0);
			glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
			glMatrixMode ( GL_MODELVIEW );
			glLoadIdentity();
			*/
			Opengl2md2::getInstance().reshape(int(Width),int(Height));
		}

		/*
		/// <summary>
		/// Event handler called when the control is resized.
		/// </summary>
		void KeydownOpenGL(EventArgs^ e)
		{
			UNREF(e);

			if(m_hDC == NULL || m_hRC == NULL)
				return;

			if(Width == 0 || Height == 0)
				return;

			Opengl2md2::getInstance().reshape(int(Width),int(Height));
		}*/
	};
};
