#include "jk_check1.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Pixel_Ground.h"
#include "jk_SONIC.h"

namespace jk
{
	check1::check1()
		: mCollider(nullptr)
		, mGround(nullptr)
	{
	}
	check1::~check1()
	{
	}
	void check1::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 150.0f));
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 26151.f, 3333.f });
		Gameobject::Initialize();
	}
	void check1::Update()
	{
		Gameobject::Update();
	}
	void check1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void check1::Release()
	{
		Gameobject::Release();
	}
	void check1::OnCollisionEnter(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mGround->Set_Circlecheck(1); 
		}		
	}
	void check1::OnCollisionStay(Collider* other)
	{
	}
	void check1::OnCollisionExit(Collider* other)
	{
	}
}