#include "jk_Act1_BG_object.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Resources.h"

#include "jk_SONIC.h"
#include "jk_Camera.h"
#include "jk_Time.h"
#include "jk_Input.h"


namespace jk
{

	Act1_BG_object::Act1_BG_object()
		: mImage(nullptr)
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
			Vector2 pos = tr->GetPos();
			Vector2 mpos = pos - (Camera::CaluatePos(pos) - pos);
		
			TransparentBlt(hdc, 0, 0, 1200, 840, mImage->GetHdc(), mpos.x, mpos.y, 1200, 840, RGB(13, 72, 7));
	}


	void Act1_BG_object::Release()
	{
		Gameobject::Release();
	}

}
