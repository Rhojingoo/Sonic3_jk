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

		//�����
		HBITMAP mBackBuffer; //������ ��ȭ�� �ϳ� �����
		HDC mBackHDC; //���ο� ��ȭ���� �׸����׸������� �����ϳ� �߰�

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}