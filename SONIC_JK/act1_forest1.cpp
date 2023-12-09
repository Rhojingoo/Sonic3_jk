#include "act1_forest1.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	act1_forest1::act1_forest1()
		:mImage(nullptr)
	{
	}
	act1_forest1::~act1_forest1()
	{
	}
	void act1_forest1::Initialize()
	{
		mImage = Resources::Load<Image>(L"forestup", L"..\\Resources\\forestup.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 2790.0f * 3, (940.0f * 3 - 40) });
		Gameobject::Initialize();
	}
	void act1_forest1::Update()
	{
		Gameobject::Update();
	}
	void act1_forest1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);
		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, static_cast<int>(mpos.x / 4.1f), static_cast<int>(mpos.y), 12515, 340,
			mImage->GetHdc(), 21, 14, 12515, 340, RGB(13, 72, 7));
	}

	void act1_forest1::Release()
	{
		Gameobject::Release();
	}
}
