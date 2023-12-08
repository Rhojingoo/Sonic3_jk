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
		//GetSystemMetrics �������� sm_cxscreen
			
		mWidth = 1200;//GetSystemMetrics(SM_CXSCREEN);
		mHeight = 840;//GetSystemMetrics(SM_CYSCREEN); 

		//��Ʈ�� �ػ󵵸� �����ϱ� ���� ���� ������ ũ�⸦ ������ش�.
		RECT rect = { 0, 0, mWidth , mHeight }; //RECT(�޸�Ŭ���ڷ���) rect �簢���� ������ �����ϴ� �Լ�
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);  // �����ϴ�

		// ������ ũ�� ����� ��� ����
		SetWindowPos(mHwnd
			, nullptr, 100, 50  //������ġ
			, rect.right - rect.left //���α���
			, rect.bottom - rect.top //���α���
			, 0);
		ShowWindow(hWnd, true);  //������ ȭ�� �ٿ��


		//����� �ʱ�ȭ �� ����(�������)
		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight); //���ο� ��ȭ���� �����
		mBackHDC = CreateCompatibleDC(mHdc);

		//��Ʈ�� ����(������ȭ�� ����)
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
		Rectangle(mBackHDC, -1, -1, 1602, 902); //����۷� �׸���

		Input::Render(mBackHDC);				//����۷� �׸��� 
		SceneManager::Render(mBackHDC);			//����۷� �׸��� 
		Time::Render(mBackHDC);					//����۷� �׸��� 

		// ����ۿ� �ִ� �׸��� �������ۿ� �׷�����Ѵ�.
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