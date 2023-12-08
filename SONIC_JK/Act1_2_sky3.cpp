#include "Act1_2_sky3.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	Act1_2_sky3::Act1_2_sky3()
		:mImage(nullptr)
	{
	}
	Act1_2_sky3::~Act1_2_sky3()
	{
	}
	void Act1_2_sky3::Initialize()
	{
		mImage = Resources::Load<Image>(L"act1-2_sky3", L"..\\Resources\\ActBG_1_2\\sky_bg\\act1-2_sky3.bmp");
		Transform* tr = GetComponent<Transform>();		
		Gameobject::Initialize();
	}
	void Act1_2_sky3::Update()
	{
		Gameobject::Update();
	}
	void Act1_2_sky3::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);
		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, static_cast<int>(mpos.x / 3.3f), static_cast<int>(mpos.y), 14064, 240,
			mImage->GetHdc(), 0, 0, 14064, 240, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Act1_2_sky3::Release()
	{
		Gameobject::Release();
	}
}