#include "Act1_2_sky5.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	Act1_2_sky5::Act1_2_sky5()
	{
	}
	Act1_2_sky5::~Act1_2_sky5()
	{
	}
	void Act1_2_sky5::Initialize()
	{
		mImage = Resources::Load<Image>(L"act1-2_sky5", L"..\\Resources\\ActBG_1_2\\sky_bg\\act1-2_sky5.bmp");
		Transform* tr = GetComponent<Transform>();
		Gameobject::Initialize();
	}
	void Act1_2_sky5::Update()
	{
		Gameobject::Update();
	}
	void Act1_2_sky5::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 5.1f, mpos.y, 14064, 288, mImage->GetHdc(), 0, 0, 14064, 288, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void Act1_2_sky5::Release()
	{
		Gameobject::Release();
	}
}
