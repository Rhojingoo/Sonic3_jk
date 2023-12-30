#include "UI_framework.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Input.h"

namespace jk
{
	UI_framework::UI_framework()
		:mTime(0)
		,mTime2(0)
		,mImage(nullptr)
	{
	}

	UI_framework::~UI_framework()
	{
	}

	void UI_framework::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI_Framework", L"..\\Resources\\UI\\UI_Framework.bmp");
		Gameobject::Initialize();
	}

	void UI_framework::Update()
	{
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
			mTime = 10;
		}

		if (mTime2 >= 60)
		{
			mTime2 = 0;
		}
		Gameobject::Update();
	}

	void UI_framework::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		TransparentBlt(hdc, 0 , 0, 1200, 840, mImage->GetHdc(), 0, 0, 400, 240, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}

	void UI_framework::Release()
	{
		Gameobject::Release();
	}
}