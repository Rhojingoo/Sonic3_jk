#include "Act1_2_sky4.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	Act1_2_sky4::Act1_2_sky4()
		:mImage(nullptr)
	{
	}
	Act1_2_sky4::~Act1_2_sky4()
	{
	}
	void Act1_2_sky4::Initialize()
	{
		mImage = Resources::Load<Image>(L"act1-2_sky4", L"..\\Resources\\ActBG_1_2\\sky_bg\\act1-2_sky4.bmp");
		Transform* tr = GetComponent<Transform>();
		Gameobject::Initialize();
	}
	void Act1_2_sky4::Update()
	{
		Gameobject::Update();
	}
	void Act1_2_sky4::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, static_cast<int>(mpos.x / 3.6f), static_cast<int>(mpos.y), 14064, 432,
			mImage->GetHdc(), 0, 0, 14064, 432, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Act1_2_sky4::Release()
	{
		Gameobject::Release();
	}
}
