#include "Add_force.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"


namespace jk
{
	Add_force::Add_force()
		: mCollider(nullptr)
		, mRigidbody(nullptr)
		, up_add(0)
	{
	}
	Add_force::~Add_force()
	{
	}
	void Add_force::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 250.f));		
		Transform* tr = GetComponent<Transform>();
		Gameobject::Initialize();
	}
	void Add_force::Update()
	{
		Gameobject::Update();
	}
	void Add_force::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Add_force::Release()
	{
		Gameobject::Release();
	}
	void Add_force::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{

		}
	}
	void Add_force::OnCollisionStay(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			if (up_add == 0)
			{
				Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
				mSonic_rb->AddForce(Vector2{ 10000.f,0.f });
			}	
			if (up_add == 1)
			{
				Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
				mSonic_rb->AddForce(Vector2{ 0.f,-10000.f });
				mSonic_rb->SetVelocity(Vector2{ 0.f,-10000.f });
				mSonic_rb->SetGround(false);
			}
		}
	}
	void Add_force::OnCollisionExit(Collider* other)
	{
	}
	void Add_force::idle()
	{
	}
	void Add_force::death()
	{
	}
}
