#include "UI_Time.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Time.h"
#include "jk_Image.h"


namespace jk
{
	UI_Time::UI_Time()
		:mTime2(0)
		, mTime(0)
		, mTime_S(0)
		, mTime_M(0)
		, mImage(nullptr)
	{
	}
	UI_Time::~UI_Time()
	{
	}
	void UI_Time::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void UI_Time::Update()
	{
		mTime2 += static_cast<float>(Time::DeltaTime());

		if ((mTime2 >= 1.f) && (mTime2 < 2.f))
		{
			mTime = 1;
		}
		if ((mTime2 >= 2.f) && (mTime2 < 3.f))
		{
			mTime = 2;
		}
		if ((mTime2 >= 3.f) && (mTime2 < 4.f))
		{
			mTime = 3;
		}
		if ((mTime2 >= 4.f) && (mTime2 < 5.f))
		{
			mTime = 4;
		}
		if ((mTime2 >= 5.f) && (mTime2 < 6.f))
		{
			mTime = 5;
		}
		if ((mTime2 >= 6.f) && (mTime2 < 7.f))
		{
			mTime = 6;
		}
		if ((mTime2 >= 7.f) && (mTime2 < 8.f))
		{
			mTime = 7;
		}
		if ((mTime2 >= 8.f) && (mTime2 < 9.f))
		{
			mTime = 8;
		}
		if ((mTime2 >= 9.f) && (mTime2 < 10.f))
		{
			mTime = 9;
		}
		if ((mTime2 >= 10.f) && (mTime2 < 11.f))
		{
			mTime = 0;
			mTime2 = 0;
			mTime_S += 1;
		}


		if (mTime_S >= 6)
		{
			mTime_S = 0;
			mTime_M += 1;
		}

		if (mTime_M >= 10)
		{
			mTime_M = 0;
		}


		Gameobject::Update();
	}
	void UI_Time::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);
		int a = 9;
		int b = 58;
		if (mTime == 0)
		{
			a = 9;
			b = 58;
		}
		if (mTime == 1)
		{
			a = 18;
			b = 58;
		}
		if (mTime == 2)
		{
			a = 27;
			b = 58;
		}
		if (mTime == 3)
		{
			a = 36;
			b = 58;
		}
		if (mTime == 4)
		{
			a = 45;
			b = 58;
		}
		if (mTime == 5)
		{
			a = 54;
			b = 58;
		}
		if (mTime == 6)
		{
			a = 63;
			b = 58;
		}

		if (mTime == 7)
		{
			a = 72;
			b = 58;
		}
		if (mTime == 8)
		{
			a = 81;
			b = 58;
		}
		if (mTime == 9)
		{
			a = 90;
			b = 58;
		}

		TransparentBlt(hdc, 237, 91, 21, 33, mImage->GetHdc(), a, b, 7, 11, RGB(13, 72, 7));
		Gameobject::Render(hdc);
	}
	void UI_Time::Release()
	{
		Gameobject::Release();
	}
}
