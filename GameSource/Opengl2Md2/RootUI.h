#pragma once
#include "IEventHandler.h"
#include <vector>
#include "Penal.h"
#include <string>


using namespace std;
namespace GameEngine
{
	class DllExport RootUI : public Penal
	{
	private:
		vector<IEventHandler<ClickEventArgs>*> TouchEvent;


	public:
		RootUI();

	public:
		void addEventHandler(IEventHandler<ClickEventArgs>* handler);

	public:
		void onTouchEvent(MotionEvent event);


	public:
		virtual void OnCreate() { }

	public:

	public:
		virtual void OnTouch(UIBase* sender, ClickEventArgs e) {	}

	public:
		virtual void OnShow() { }

	public:
		virtual void onClose() {}

	public:
		void onUpdate(long long dt) {}

	public:
		void OnDraw(bool isSelect = false);


		void Save();

		bool Load(string str);

	};
}