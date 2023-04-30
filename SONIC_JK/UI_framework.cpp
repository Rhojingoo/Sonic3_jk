#include "UI_framework.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Titlesonic.h"


namespace jk
{
	UI_framework::UI_framework()
		:mTime(0)
		,time(0)
	{
	}

	UI_framework::~UI_framework()
	{
	}

	void UI_framework::Initialize()
	{
		mImage = Resources::Load<Image>(L"UI_Framework", L"..\\Resources\\UI\\UI_Framework.bmp");





		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2{ 2790.0f * 3, (940.0f * 3 + 300) });
	
		Gameobject::Initialize();
	}

	void UI_framework::Update()
	{
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
			mTime = 10;
		}

		if (time >= 60)
		{
			time = 0;
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