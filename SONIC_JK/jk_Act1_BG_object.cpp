#include "jk_Act1_BG_object.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"
#include "jk_SONIC.h"


namespace jk
{

	Act1_BG_object::Act1_BG_object()
		:Check_BG(0)
		, mSonic_pos(0.f,0.f)
	{
	}

	Act1_BG_object ::~Act1_BG_object()
	{
	}

	void Act1_BG_object::Initialize()
	{
		mImage = Resources::Load<Image>(L"BG", L"..\\Resources\\BG.bmp");

		Gameobject::Initialize();
	}


	void Act1_BG_object::Update()
	{
		mSonic_pos = mOwner->GetComponent<Transform>()->GetPos();
		
		if (mSonic_pos.x >= 30300)
		{
			Check_BG = 1;
		}

		Gameobject::Update();

	}


	void Act1_BG_object::Render(HDC hdc)
	{

			Gameobject::Render(hdc);
			Transform* tr = GetComponent<Transform>();				
			//tr->SetPos(Vector2 { 2790.0f*3, 940.0f*3-120 });
				
			Vector2 pos = tr->GetPos();
			Vector2 mpos = pos - (Camera::CaluatePos(pos) - pos);
		
			TransparentBlt(hdc, 0, 0, 1200, 840, mImage->GetHdc(), mpos.x, mpos.y, 1200, 840, RGB(13, 72, 7));

	}


	void Act1_BG_object::Release()
	{
		Gameobject::Release();
	}

}
