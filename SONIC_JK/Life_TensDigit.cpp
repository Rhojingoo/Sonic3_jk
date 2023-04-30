#include "Life_TensDigit.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"

namespace jk
{
	Life_TensDigit::Life_TensDigit(Gameobject* owner)
		:TensDigit(0)
		, Units(nullptr)
		, mOwner(nullptr)
		, mImage(nullptr)
	{
		mOwner = owner;
		Units = dynamic_cast<Life_Manager*>(owner);
	}
	Life_TensDigit::~Life_TensDigit()
	{
	}
	void Life_TensDigit::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void Life_TensDigit::Update()
	{
		TensDigit = Units->GetSonicLife_TensDigit();
		Gameobject::Update();
	}
	void Life_TensDigit::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 71;
		if (TensDigit == 0)
		{
			a = 9;
			b = 71;
		}
		if (TensDigit == 1)
		{
			a = 18;
			b = 71;
		}
		if (TensDigit == 2)
		{
			a = 27;
			b = 71;
		}
		if (TensDigit == 3)
		{
			a = 36;
			b = 71;
		}
		if (TensDigit == 4)
		{
			a = 45;
			b = 71;
		}
		if (TensDigit == 5)
		{
			a = 54;
			b = 71;
		}
		if (TensDigit == 6)
		{
			a = 63;
			b = 71;
		}
		if (TensDigit == 7)
		{
			a = 72;
			b = 71;
		}
		if (TensDigit == 8)
		{
			a = 81;
			b = 71;
		}
		if (TensDigit == 9)
		{
			a = 90;
			b = 71;
		}

		TransparentBlt(hdc, 150, 756, 21, 21, mImage->GetHdc(), a, b, 7, 7, RGB(13, 72, 7));


	}
	void Life_TensDigit::Release()
	{
		Gameobject::Release();
	}
}
