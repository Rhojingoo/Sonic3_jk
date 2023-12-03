#include "jk_check2.h"
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
	check2::check2()
		: mCollider(nullptr)
		, mGround(nullptr)
	{
	}
	check2::~check2()
	{
	}
	void check2::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 150.0f));
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 26991.f,2928.f });

		Gameobject::Initialize();
	}
	void check2::Update()
	{
		Gameobject::Update();
	}
	void check2::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void check2::Release()
	{
		Gameobject::Release();
	}
	void check2::OnCollisionEnter(Collider* other)
	{		
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{	
			mGround->Set_Circle_Center(Vector2{26823.f,2637.f});		
			mGround->CheckLoopEnter_R();		
		}
	}
	void check2::OnCollisionStay(Collider* other)
	{
	}
	void check2::OnCollisionExit(Collider* other)
	{
	}
}