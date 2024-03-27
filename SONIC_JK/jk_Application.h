#pragma once
#include "SONIC_Engine.h"

namespace jk
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void Render();
		void Init_Sc();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clear();

	private:
		HWND mHwnd;
		HDC mHdc;

		//백버퍼
		HBITMAP mBackBuffer; //윈도우 도화지 하나 만들기
		HDC mBackHDC; //새로운 도화지에 그림을그리기위한 도구하나 추가

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}