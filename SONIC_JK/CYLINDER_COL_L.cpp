#include "CYLINDER_COL_L.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"

namespace jk
{
	CYLINDER_COL_L::CYLINDER_COL_L(Gameobject* owner)
		:mOwner(owner)
	{
		mOwner = owner;
		sonic = dynamic_cast<Sonic*>(owner);
	}
	CYLINDER_COL_L::~CYLINDER_COL_L()
	{
	}
	void CYLINDER_COL_L::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(30.0f, 1250.f));
		Transform* tr = GetComponent<Transform>();


		Gameobject::Initialize();
	}
	void CYLINDER_COL_L::Update()
	{
		Gameobject::Update();
	}
	void CYLINDER_COL_L::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void CYLINDER_COL_L::Release()
	{
		Gameobject::Release();
	}
	void CYLINDER_COL_L::OnCollisionEnter(Collider* other)
	{
	
	}
	void CYLINDER_COL_L::OnCollisionStay(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonic->Getsonicstate();
			Vector2 Sonic_Velocity(0.f, 0.f);


			Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
			Sonic_Velocity = mSonic_rb->GetVelocity();
			Sonic_Velocity.x = 10000.f;
			mSonic_rb->AddForce(Vector2{ Sonic_Velocity.x,Sonic_Velocity.y });
		}
	}
	void CYLINDER_COL_L::OnCollisionExit(Collider* other)
	{
	}
	void CYLINDER_COL_L::idle()
	{
	}
}
