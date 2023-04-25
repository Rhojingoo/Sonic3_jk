#include "act2_water.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Object.h"
#include "jk_Collider.h"
#include "jk_Camera.h"
#include "jk_Water_effect.h"
#include "jk_SONIC.h"



namespace jk
{
	act2_water::act2_water()
	{
	}
	act2_water::~act2_water()
	{
	}
	void act2_water::Initialize()
	{
		mImage = Resources::Load<Image>(L"AcT2_WATER", L"..\\Resources\\AcT1_WATER.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(Vector2{ 4665.f,  4755.f });
		//1555,1585
		float pos_y = mImage->GetHeight() * 3.5;
		float pos_x = mImage->GetWidth() * 3;

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(pos_x, pos_y));
		//Vector2 size = collider->GetSize();
		//collider->SetCenter(Vector2{ (-0.0f) * size.x, (-0.f) * size.y });

		Gameobject::Initialize();
	}
	void act2_water::Update()
	{
		Gameobject::Update();
	}
	void act2_water::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		checktime = 120.0f;
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = (BYTE)checktime;
		Vector2 mpos = Camera::CaluatePos(pos);

		AlphaBlend(hdc, mpos.x, mpos.y, mImage->GetWidth() * 10, mImage->GetHeight() * 15, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

		Gameobject::Render(hdc);
	}
	void act2_water::Release()
	{
		Gameobject::Release();
	}
	void act2_water::OnCollisionEnter(Collider* other)
	{
	}
	void act2_water::OnCollisionStay(Collider* other)
	{
	}
	void act2_water::OnCollisionExit(Collider* other)
	{
	}
}