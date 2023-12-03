#include "UI_Time_seconds.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"


float time_S;

namespace jk
{
	UI_Time_seconds::UI_Time_seconds(Gameobject* owner)
		: mOwner(owner)
		, seconds(nullptr)
		, mImage(nullptr)
		, time_S(0.f)
	{		
		seconds = dynamic_cast<UI_Time*>(owner);
	}
	UI_Time_seconds::~UI_Time_seconds()
	{
	}
	void UI_Time_seconds::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void UI_Time_seconds::Update()
	{
		time_S =seconds->Get_seconds();			

		Gameobject::Update();
	}
	void UI_Time_seconds::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 58;
		if (time_S == 0)
		{
			a = 9;
			b = 58;
		}
		if (time_S == 1)
		{
			a = 18;
			b = 58;
		}
		if (time_S == 2)
		{
			a = 27;
			b = 58;
		}
		if (time_S == 3)
		{
			a = 36;
			b = 58;
		}
		if (time_S == 4)
		{
			a = 45;
			b = 58;
		}
		if (time_S == 5)
		{
			a = 54;
			b = 58;
		}

		TransparentBlt(hdc, 213, 91, 21, 33, mImage->GetHdc(), a, b, 7, 11, RGB(13, 72, 7));
		Gameobject::Render(hdc);

		Gameobject::Render(hdc);
	}
	void UI_Time_seconds::Release()
	{
		Gameobject::Release();
	}
}