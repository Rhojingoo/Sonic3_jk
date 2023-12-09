#include "midlesky.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	midlesky::midlesky()
		:mImage(nullptr)
	{
	}
	midlesky::~midlesky()
	{
	}
	void midlesky::Initialize()
	{
		mImage = Resources::Load<Image>(L"mksy", L"..\\Resources\\mksy.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 2790.0f * 3, (940.0f * 3 - 175) });
		Gameobject::Initialize();
	}
	void midlesky::Update()
	{
		Gameobject::Update();
	}
	void midlesky::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);
		Vector2 mpos = Camera::CaluatePos(pos);

		TransparentBlt(hdc, static_cast<int>(mpos.x / 3.f), static_cast<int>(mpos.y), 15166, 48,
			mImage->GetHdc(), 0, 34, 15166, 48, RGB(13, 72, 7));
	}
	void midlesky::Release()
	{
		Gameobject::Release();
	}
}
