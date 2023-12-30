#include "Act1_2_sky1.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"
#include "jk_Image.h"

namespace jk
{
	Act1_2_sky1::Act1_2_sky1()
		:mImage(nullptr)
	{
	}
	Act1_2_sky1::~Act1_2_sky1()
	{
	}
	void Act1_2_sky1::Initialize()
	{
		mImage = Resources::Load<Image>(L"act1-2_sky1", L"..\\Resources\\ActBG_1_2\\sky_bg\\act1-2_sky1.bmp");
		Transform* tr = GetComponent<Transform>();
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
		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, static_cast<int>(mpos.x / 3.f), static_cast<int>(mpos.y), static_cast<int>(14064.f), static_cast<int>(45.f),
			mImage->GetHdc(), static_cast<int>(0.f), static_cast<int>(0.f), static_cast<int>(14064.f), static_cast<int>(45.f), RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Act1_2_sky1::Release()
	{
		Gameobject::Release();
	}
}
