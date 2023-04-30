#include "Life_UnitsDigit.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"



namespace jk
{
	Life_UnitsDigit::Life_UnitsDigit(Gameobject* owner)
		:UnitsDigit(0)
		, Units(nullptr)
		, mOwner(nullptr)
		, mImage(nullptr)
	{
		mOwner = owner;
		Units = dynamic_cast<Life_Manager*>(owner);
	}
	Life_UnitsDigit::~Life_UnitsDigit()
	{
	}
	void Life_UnitsDigit::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void Life_UnitsDigit::Update()
	{
		UnitsDigit = Units->GetSonicLife_UnitsDigit();
		Gameobject::Update();
	}
	void Life_UnitsDigit::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 71;
		if (UnitsDigit == 0)
		{
			a = 9;
			b = 71;
		}
		if (UnitsDigit == 1)
		{
			a = 18;
			b = 71;
		}
		if (UnitsDigit == 2)
		{
			a = 27;
			b = 71;
		}
		if (UnitsDigit == 3)
		{
			a = 36;
			b = 71;
		}
		if (UnitsDigit == 4)
		{
			a = 45;
			b = 71;
		}
		if (UnitsDigit == 5)
		{
			a = 54;
			b = 71;
		}
		if (UnitsDigit == 6)
		{
			a = 63;
			b = 71;
		}
		if (UnitsDigit == 7)
		{
			a = 72;
			b = 71;
		}
		if (UnitsDigit == 8)
		{
			a = 81;
			b = 71;
		}
		if (UnitsDigit == 9)
		{
			a = 90;
			b = 71;
		}

		TransparentBlt(hdc, 174, 756, 21, 21, mImage->GetHdc(), a, b, 7, 7, RGB(13, 72, 7));


		Gameobject::Render(hdc);
	}
	void Life_UnitsDigit::Release()
	{
		Gameobject::Release();
	}
}
