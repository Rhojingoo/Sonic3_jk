#include "Act1_2_sky1.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	Act1_2_sky1::Act1_2_sky1()
	{
	}
	Act1_2_sky1::~Act1_2_sky1()
	{
	}
	void Act1_2_sky1::Initialize()
	{
		mImage = Resources::Load<Image>(L"act1-2_sky1", L"..\\Resources\\ActBG_1_2\\sky_bg\\act1-2_sky1.bmp");
		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2{ 0.f, 46.f });
		Gameobject::Initialize();
	}
	void Act1_2_sky1::Update()
	{
		Gameobject::Update();
	}
	void Act1_2_sky1::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);
	
		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 3.f, mpos.y, 14064, 45, mImage->GetHdc(), 0, 0, 14064, 45, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Act1_2_sky1::Release()
	{
		Gameobject::Release();
	}
}
