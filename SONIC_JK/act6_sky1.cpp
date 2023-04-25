#include "act6_sky1.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	act6_sky1::act6_sky1()
	{
	}
	act6_sky1::~act6_sky1()
	{
	}
	void act6_sky1::Initialize()
	{
		mImage = Resources::Load<Image>(L"act6_sky1", L"..\\Resources\\ActBG_6\\act6_sky1.bmp");
		Transform* tr = GetComponent<Transform>();
		
		Gameobject::Initialize();
	}
	void act6_sky1::Update()
	{
		Gameobject::Update();
	}
	void act6_sky1::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 3.5f, mpos.y, 21000, 432, mImage->GetHdc(), 0, 0, 21000, 432, RGB(13, 72, 7));

		Gameobject::Render(hdc);
	}
	void act6_sky1::Release()
	{
		Gameobject::Release();
	}
}