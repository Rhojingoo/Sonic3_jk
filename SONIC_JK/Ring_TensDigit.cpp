#include "Ring_TensDigit.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"


namespace jk
{
	Ring_TensDigit::Ring_TensDigit(Gameobject* owner)
		:TensDigit(0)	
		, Units(nullptr)
		, mOwner(owner)
		, mImage(nullptr)
	{	
		Units = dynamic_cast<Ring_Point_Manager*>(owner);
	}
	Ring_TensDigit::~Ring_TensDigit()
	{
	}
	void Ring_TensDigit::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void Ring_TensDigit::Update()
	{
		TensDigit = Units->GetRingPoint_TensDigit();

		Gameobject::Update();
	}
	void Ring_TensDigit::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 58;
		if (TensDigit == 0)
		{
			a = 9;
			b = 58;
		}
		if (TensDigit == 1)
		{
			a = 18;
			b = 58;
		}
		if (TensDigit == 2)
		{
			a = 27;
			b = 58;
		}
		if (TensDigit == 3)
		{
			a = 36;
			b = 58;
		}
		if (TensDigit == 4)
		{
			a = 45;
			b = 58;
		}
		if (TensDigit == 5)
		{
			a = 54;
			b = 58;
		}
		if (TensDigit == 6)
		{
			a = 63;
			b = 58;
		}
		if (TensDigit == 7)
		{
			a = 72;
			b = 58;
		}
		if (TensDigit == 8)
		{
			a = 81;
			b = 58;
		}
		if (TensDigit == 9)
		{
			a = 90;
			b = 58;
		}

		TransparentBlt(hdc, 213, 147, 21, 33, mImage->GetHdc(), a, b, 7, 11, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Ring_TensDigit::Release()
	{
		Gameobject::Release();
	}
}