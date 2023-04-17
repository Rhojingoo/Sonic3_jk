#include "acr1_forest2.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Camera.h"

namespace jk
{
	acr1_forest2::acr1_forest2()
	{
	}
	acr1_forest2::~acr1_forest2()
	{
		
	}
	void acr1_forest2::Initialize()
	{
		mImage = Resources::Load<Image>(L"middlesky", L"..\\Resources\\middlesky.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{2790.0f * 3, (940.0f * 3 - 127) });
		Gameobject::Initialize();
	}
	void acr1_forest2::Update()
	{
		Gameobject::Update();
	}
	void acr1_forest2::Render(HDC hdc)
	{
		Gameobject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(pos);
		Vector2 imagepos = Vector2(11515, 1026);
		Vector2 mpos = Camera::CaluatePos(pos);
		TransparentBlt(hdc, mpos.x / 3.f, mpos.y, 11590, 87, mImage->GetHdc(), 7, 1, 11590, 87, RGB(13, 72, 7));
	}

	void acr1_forest2::Release()
	{
		Gameobject::Release();
	}
}
