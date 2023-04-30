#include "Ring_UnitsDigit.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"


namespace jk
{
	Ring_UnitsDigit::Ring_UnitsDigit(Gameobject* owner)
		:UnitsDigit(0)
		, Units(nullptr)
		, mOwner(nullptr)
		, mImage(nullptr)
	{	
		mOwner = owner;
		Units = dynamic_cast<Ring_Point_Manager*>(owner);
	}

	Ring_UnitsDigit::~Ring_UnitsDigit()
	{
	}
	void Ring_UnitsDigit::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void Ring_UnitsDigit::Update()
	{
		UnitsDigit = Units->GetRingPoint_UnitsDigit();

		Gameobject::Update();
	}
	void Ring_UnitsDigit::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 58;
		if (UnitsDigit == 0)
		{
			a = 9;
			b = 58;
		}
		if (UnitsDigit == 1)
		{
			a = 18;
			b = 58;
		}
		if (UnitsDigit == 2)
		{
			a = 27;
			b = 58;
		}
		if (UnitsDigit == 3)
		{
			a = 36;
			b = 58;
		}
		if (UnitsDigit == 4)
		{
			a = 45;
			b = 58;
		}
		if (UnitsDigit == 5)
		{
			a = 54;
			b = 58;
		}
		if (UnitsDigit == 6)
		{
			a = 63;
			b = 58;
		}
		if (UnitsDigit == 7)
		{
			a = 72;
			b = 58;
		}
		if (UnitsDigit == 8)
		{
			a = 81;
			b = 58;
		}
		if (UnitsDigit == 9)
		{
			a = 90;
			b = 58;
		}

		TransparentBlt(hdc, 237, 147, 21, 33, mImage->GetHdc(), a, b, 7, 11, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Ring_UnitsDigit::Release()
	{
		Gameobject::Release();
	}
}