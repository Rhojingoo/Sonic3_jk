#include "jk_Sky.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	Sky::Sky()
		:mImage(nullptr)
	{
	}
	Sky::~Sky()
	{
	}
	void Sky::Initialize()
	{
		mImage = Resources::Load<Image>(L"Sky", L"..\\Resources\\Sky.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 2790.0f * 3, (940.0f * 3 -1270) });
		Gameobject::Initialize();
	}
	void Sky::Update()
	{
		Gameobject::Update();
	}
	void Sky::Render(HDC hdc)
	{			
		Gameobject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);
		Vector2 mpos = Camera::CaluatePos(pos);	
		TransparentBlt(hdc, mpos.x / 3.f, mpos.y, 15160.0f, 1100.0f, mImage->GetHdc(), 0, 34, 15160.0f, 1100.0f, RGB(13, 72, 7));
	}
	void Sky::Release()
	{
		Gameobject::Release();
	}
}
