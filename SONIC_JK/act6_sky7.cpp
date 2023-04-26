#include "act6_sky7.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	act6_sky7::act6_sky7()
	{
	}
	act6_sky7::~act6_sky7()
	{
	}
	void act6_sky7::Initialize()
	{
		mImage = Resources::Load<Image>(L"act6_sky7", L"..\\Resources\\ActBG_6\\act6_sky7.bmp");
		Transform* tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void act6_sky7::Update()
	{
		Gameobject::Update();
	}
	void act6_sky7::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 5.f, mpos.y, 21000, 288, mImage->GetHdc(), 0, 0, 21000, 288, RGB(13, 72, 7));


		Gameobject::Render(hdc);
	}
	void act6_sky7::Release()
	{
		Gameobject::Release();
	}
}