#include "jk_Application.h"
#include "jk_SceneManager.h"
#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_CollisionManager.h"
#include "jk_Camera.h"
#include "SoundManager.h"

namespace jk
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mBackBuffer(nullptr)
		
	{
	}

	Application::~Application()
	{
		/*SceneManager::Release();*/
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		//GetSystemMetrics 꽉찬넓이 sm_cxscreen
			
		mWidth = 1200;//GetSystemMetrics(SM_CXSCREEN);
		mHeight = 840;//GetSystemMetrics(SM_CYSCREEN); 

		//비트맵 해상도를 설정하기 위한 실제 윈도우 크기를 계산해준다.
		RECT rect = { 0, 0, mWidth , mHeight }; //RECT(메모클라스자료형) rect 사각형의 범위를 지정하는 함수
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);  // 조정하다

		// 윈도우 크기 변경및 출력 설정
		SetWindowPos(mHwnd
			, nullptr, 100, 50  //시작위치
			, rect.right - rect.left //가로길이
			, rect.bottom - rect.top //세로길이
			, 0);
		ShowWindow(hWnd, true);  //윈도우 화면 뛰우기


		//백버퍼 초기화 및 설정(정보등록)
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight); //새로운 도화지를 만든다
		mBackHDC = CreateCompatibleDC(mHdc);

		//비트맵 셀렉(기존도화지 설정)
		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHDC, mBackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initiailize();
		Input::Initialize();
		SoundManager::Initialize();
		SceneManager::Initialize();

		Camera::Initialize();
		
	}

	void Application::Run()
	{
		Update();
		Render();	
		SceneManager::Destroy();
	}

	void Application::Update()
	{
		
		Time::Update();
		Input::Update();
		Camera::Update();

		SceneManager::Update();
		CollisionManager::Update();

	}

	void Application::Render()
	{
		Rectangle(mBackHDC, -1, -1, 1602, 902); //백버퍼로 그리기

		Input::Render(mBackHDC);				//백버퍼로 그리기 
		SceneManager::Render(mBackHDC);			//백버퍼로 그리기 
		Time::Render(mBackHDC);					//백버퍼로 그리기 

		// 백버퍼에 있는 그림을 원본버퍼에 그려줘야한다.
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHDC, 0, 0, SRCCOPY);
	}

	void Application::clear()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(121, 121, 121));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHDC, grayBrush);
		Rectangle(mBackHDC, -1, -1, 1602, 902);
		SelectObject(mBackHDC, oldBrush);
		DeleteObject(grayBrush);
	}
}