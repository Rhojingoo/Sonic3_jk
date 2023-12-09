#include "jk_Act1_2_BG.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	Act1_2_BG::Act1_2_BG()
		:mImage(nullptr)
	{
	}
	Act1_2_BG::~Act1_2_BG()
	{
	}
	void Act1_2_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"BG_Act1_2", L"..\\Resources\\BG_Act1_2.bmp");

		Gameobject::Initialize();
	}
	void Act1_2_BG::Update()
	{
		Gameobject::Update();
	}
	void Act1_2_BG::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 mpos = pos - (Camera::CaluatePos(pos) - pos);
		TransparentBlt(hdc, 0, 0, 1200, 840,
			mImage->GetHdc(), static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(4, 20, 83));
		Gameobject::Render(hdc);
	}
	void Act1_2_BG::Release()
	{
		Gameobject::Release();
	}
}