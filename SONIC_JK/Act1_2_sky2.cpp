#include "Act1_2_sky2.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	Act1_2_sky2::Act1_2_sky2()
	{
	}
	Act1_2_sky2::~Act1_2_sky2()
	{
	}

	void Act1_2_sky2::Initialize()
	{
		mImage = Resources::Load<Image>(L"act2_sky2", L"..\\Resources\\ActBG_1_2\\act2_sky2.bmp");
		Transform* tr = GetComponent<Transform>();
		
		Gameobject::Initialize();
	}

	void Act1_2_sky2::Update()
	{
		Gameobject::Update();
	}

	void Act1_2_sky2::Render(HDC hdc)
	{		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x, mpos.y, 14064, 897, mImage->GetHdc(), 0, 0, 14064, 897, RGB(0, 0, 0));
		Gameobject::Render(hdc);
	}

	void Act1_2_sky2::Release()
	{
		Gameobject::Release();
	}
}