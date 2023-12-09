#include "UI_Time.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Time.h"


namespace jk
{
	UI_Time::UI_Time()
		:time(0)
		, mTime(0)
		, time_S(0)
		, time_M(0)
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
		time += static_cast<float>(Time::DeltaTime());

		if ((time >= 1.f) && (time < 2.f))
		{
			mTime = 1;
		}
		if ((time >= 2.f) && (time < 3.f))
		{
			mTime = 2;
		}
		if ((time >= 3.f) && (time < 4.f))
		{
			mTime = 3;
		}
		if ((time >= 4.f) && (time < 5.f))
		{
			mTime = 4;
		}
		if ((time >= 5.f) && (time < 6.f))
		{
			mTime = 5;
		}
		if ((time >= 6.f) && (time < 7.f))
		{
			mTime = 6;
		}
		if ((time >= 7.f) && (time < 8.f))
		{
			mTime = 7;
		}
		if ((time >= 8.f) && (time < 9.f))
		{
			mTime = 8;
		}
		if ((time >= 9.f) && (time < 10.f))
		{
			mTime = 9;
		}
		if ((time >= 10.f) && (time < 11.f))
		{
			mTime = 0;
			time = 0;
			time_S += 1;
		}


		if (time_S >= 6)
		{
			time_S = 0;
			time_M += 1;
		}

		if (time_M >= 10)
		{
			time_M = 0;
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
