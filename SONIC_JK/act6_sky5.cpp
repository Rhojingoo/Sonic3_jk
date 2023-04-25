#include "act6_sky5.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	act6_sky5::act6_sky5()
	{
	}
	act6_sky5::~act6_sky5()
	{
	}
	void act6_sky5::Initialize()
	{
		mImage = Resources::Load<Image>(L"act6_sky5", L"..\\Resources\\ActBG_6\\act6_sky5.bmp");
		Transform* tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void act6_sky5::Update()
	{
		Gameobject::Update();
	}
	void act6_sky5::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 4.1f, mpos.y, 21000, 165, mImage->GetHdc(), 0, 0, 21000, 165, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void act6_sky5::Release()
	{
		Gameobject::Release();
	}
}