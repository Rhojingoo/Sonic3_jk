#include "jk_Act1_BG_object.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{

	Act1_BG_object::Act1_BG_object()
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

			//ÀüÃ¼ ÀÌ¹ÌÁö ¶Ù¿ö ÁøÇà(ÇÁ·¹ÀÎ ¶³¾îÁü)
			//tr->SetPos(Vector2 { -2790.0f*3, -940.0f*3+120 });	
			//TransparentBlt(hdc, (float)(mpos.x), (float)(mpos.y), , mImage->GetHeight(), mImage->GetHdc(), 0,0, mImage->GetWidth(), mImage->GetHeight(),  RGB(13, 72, 7));
								
			//Vector2 resolution = Vector2(1200.f, 840.f) / 2.f;
			//StretchBlt(hdc, mpos.x - resolution.x, mpos.y - resolution.y, 1200.f, 840.f, hdc, mpos.x + resolution.x, mpos.y + resolution.y, mImage->GetWidth(), mImage->GetHeight(), RGB(13, 72, 7));
			//BitBlt(hdc, mpos.x, mpos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
			//TransparentBlt(hdc, 0, 0, 1200, 840, mImage->GetHdc(), 2792, 920, 331, 255, RGB(223, 100, 128));
	}


	void Act1_BG_object::Release()
	{
		Gameobject::Release();
	}

}
