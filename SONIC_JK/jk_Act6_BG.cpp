#include "jk_Act6_BG.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"
#include "jk_SONIC.h"


namespace jk
{
	jk_Act6_BG::jk_Act6_BG()
	{
	}
	jk_Act6_BG::~jk_Act6_BG()
	{
	}
	void jk_Act6_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"act 6-Boss_map", L"..\\Resources\\ActBG_6\\act 6-Boss_map.bmp");

		Gameobject::Initialize();
	}
	void jk_Act6_BG::Update()
	{
		Gameobject::Update();
	}
	void jk_Act6_BG::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();

		Vector2 pos = tr->GetPos();
		Vector2 mpos = pos - (Camera::CaluatePos(pos) - pos);

		TransparentBlt(hdc, 0, 0, 1200, 840, mImage->GetHdc(), mpos.x, mpos.y, 1200, 840, RGB(13,72, 7));

		Gameobject::Render(hdc);
	}
	void jk_Act6_BG::Release()
	{
		Gameobject::Release();
	}
}