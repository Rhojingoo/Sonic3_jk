#include "jk_check_circle.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Object.h"
#include "jk_Ground.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"


namespace jk
{
	check_circle::check_circle()
		:checktime(0.f)
		, mImage(nullptr)
		, mTime(0.0f)
	{
	}
	check_circle::~check_circle()
	{
	}
	void check_circle::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 150.0f));
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 9195.f,3705.f });

		Gameobject::Initialize();
	}
	void check_circle::Update()
	{
		Gameobject::Update();
	}
	void check_circle::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void check_circle::Release()
	{
		Gameobject::Release();
	}
	void check_circle::OnCollisionEnter(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mGround->Set_Circlecheck(1);
			mGround->Set_Circle_Center(Vector2{ 9660.f,3720.f });
			mGround->CheckLoopEnter_R();
		}
	}
	void check_circle::OnCollisionStay(Collider* other)
	{
	}
	void check_circle::OnCollisionExit(Collider* other)
	{
	}
}
