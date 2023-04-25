#include "act6_sky4.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"


namespace jk
{
	act6_sky4::act6_sky4()
	{
	}
	act6_sky4::~act6_sky4()
	{
	}
	void act6_sky4::Initialize()
	{
		mImage = Resources::Load<Image>(L"act6_sky4", L"..\\Resources\\ActBG_6\\act6_sky4.bmp");
		Transform* tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void act6_sky4::Update()
	{
		Gameobject::Update();
	}
	void act6_sky4::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);

		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 3.8f, mpos.y, 21000, 237, mImage->GetHdc(), 0, 0, 21000, 237, RGB(13, 72, 7));


		Gameobject::Render(hdc);
	}
	void act6_sky4::Release()
	{
		Gameobject::Release();
	}
}