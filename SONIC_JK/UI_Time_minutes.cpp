#include "UI_Time_minutes.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"




namespace jk
{
	UI_Time_minutes::UI_Time_minutes(Gameobject* owner)
		:mOwner(nullptr)
	{
		mOwner = owner;
		minutes = dynamic_cast<UI_Time*>(owner);
	}
	UI_Time_minutes::~UI_Time_minutes()
	{
	}
	void UI_Time_minutes::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void UI_Time_minutes::Update()
	{
		time_M = minutes->Get_minutes();

		Gameobject::Update();
	}
	void UI_Time_minutes::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 58;
		if (time_M == 0)
		{
			a = 9;
			b = 58;
		}
		if (time_M == 1)
		{
			a = 18;
			b = 58;
		}
		if (time_M == 2)
		{
			a = 27;
			b = 58;
		}
		if (time_M == 3)
		{
			a = 36;
			b = 58;
		}
		if (time_M == 4)
		{
			a = 45;
			b = 58;
		}
		if (time_M == 5)
		{
			a = 54;
			b = 58;
		}
		if (time_M == 6)
		{
			a = 63;
			b = 58;
		}
		if (time_M == 7)
		{
			a = 72;
			b = 58;
		}
		if (time_M == 8)
		{
			a = 81;
			b = 58;
		}
		if (time_M == 9)
		{
			a = 90;
			b = 58;
		}

		TransparentBlt(hdc, 162, 91, 21, 33, mImage->GetHdc(), a, b, 7, 11, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void UI_Time_minutes::Release()
	{
		Gameobject::Release();
	}
}