#include "Add_force.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"
#include "jk_Image.h"
#include "jk_Animator.h"

namespace jk
{
	Add_force::Add_force()
		: mCollider(nullptr)
		, mRigidbody(nullptr)
		, mCheck_up(0)
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
			if (mCheck_up == 0)
			{
				Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
				mSonic_rb->AddForce(Vector2{ 10000.f,0.f });
			}
			if (mCheck_up == 1)
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


}
