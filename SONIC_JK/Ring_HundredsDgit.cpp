#include "Ring_HundredsDgit.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{
	Ring_HundredsDgit::Ring_HundredsDgit(Gameobject* owner)
		:mHundredsDigit(0)
		, mUnits(nullptr)
		, mOwner(owner)
		, mImage(nullptr)
	{	
		mUnits = dynamic_cast<Ring_Point_Manager*>(owner);
	}
	Ring_HundredsDgit::~Ring_HundredsDgit()
	{
	}
	void Ring_HundredsDgit::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI", L"..\\Resources\\UI\\UI.bmp");

		Gameobject::Initialize();
	}
	void Ring_HundredsDgit::Update()
	{
		mHundredsDigit = mUnits->GetRingPoint_HundredsDigit();

		Gameobject::Update();
	}
	void Ring_HundredsDgit::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		int a = 9;
		int b = 58;
		if (mHundredsDigit == 0)
		{
			a = 9;
			b = 58;
		}
		if (mHundredsDigit == 1)
		{
			a = 18;
			b = 58;
		}
		if (mHundredsDigit == 2)
		{
			a = 27;
			b = 58;
		}
		if (mHundredsDigit == 3)
		{
			a = 36;
			b = 58;
		}
		if (mHundredsDigit == 4)
		{
			a = 45;
			b = 58;
		}
		if (mHundredsDigit == 5)
		{
			a = 54;
			b = 58;
		}
		if (mHundredsDigit == 6)
		{
			a = 63;
			b = 58;
		}
		if (mHundredsDigit == 7)
		{
			a = 72;
			b = 58;
		}
		if (mHundredsDigit == 8)
		{
			a = 81;
			b = 58;
		}
		if (mHundredsDigit == 9)
		{
			a = 90;
			b = 58;
		}

		TransparentBlt(hdc, 189, 147, 21, 33, mImage->GetHdc(), a, b, 7, 11, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Ring_HundredsDgit::Release()
	{
		Gameobject::Release();
	}
}