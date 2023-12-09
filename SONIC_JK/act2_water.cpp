#include "act2_water.h"
#include "jk_Water_effect.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Camera.h"

namespace jk
{
	act2_water::act2_water()
		:mImage(nullptr)
		, checktime(0.f)
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
		float pos_y = mImage->GetHeight() * 3.5f;
		float pos_x = mImage->GetWidth() * 3.f;

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(pos_x, pos_y));

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

		AlphaBlend(hdc, static_cast<int>(mpos.x), static_cast<int>(mpos.y), mImage->GetWidth() * 10, mImage->GetHeight() * 15,
			mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

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