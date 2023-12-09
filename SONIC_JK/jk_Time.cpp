#include "jk_Time.h"
#include "jk_Application.h"

extern jk::Application application;

namespace jk
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};


	void Time::Initiailize()
	{		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		//double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;
		double differnceFrequency = static_cast<double>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
	
		

		//델타타임 디버그
		//#ifdef _debug
		//		if (mdeltatime > (1. / 60.))
		//			mdeltatime = (1. / 60.);
		//#endif

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			mSecond = 0.0f;
		}
	}
}