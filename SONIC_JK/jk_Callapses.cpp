#include "jk_Callapses.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"

namespace jk
{
	Callapses::Callapses()
	{
		mImage = Resources::Load<Image>(L"Rock_Platform2", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Gr_collapses", mImage, Vector2(499, 634), Vector2(136, 88), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		
		mAnimator->Play(L"Gr_collapses", true);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();
	}


	Callapses::~Callapses()
	{
	}

	void Callapses::Initialize()
	{
		Gameobject::Initialize();
	}
	void Callapses::Update()
	{
		Gameobject::Update();
	}
	void Callapses::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Callapses::Release()
	{
		Gameobject::Release();
	}
	void Callapses::OnCollisionEnter(Collider* other)
	{
		//if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		//{
		//	Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		//	rb->SetGround(true);
		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 pos = tr->GetPos();

		//	Collider* mSonic_Col = mSonic->GetComponent<Collider>();
		//	Vector2 mSonic_Pos = mSonic_Col->Getpos();
		//	Collider* groundCol = this->GetComponent<Collider>();
		//	Vector2 groundPos = groundCol->Getpos();
		//	Transform* sonicTr = mSonic->GetComponent<Transform>();
		//	Transform* grTr = this->GetComponent<Transform>();
		//	Vector2 sonic_Pos = sonicTr->GetPos();


		//	Vector2 velocity = rb->GetVelocity();
		//	velocity.y = 0.0f;
		//	rb->SetVelocity(velocity);


		//	if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
		//	{
		//		sonic_Pos.y = groundCol->Getpos().y - groundCol->GetSize().y / 2.f;			
		//		sonicTr->SetPos(sonic_Pos);
		//	}

		//	else
		//	{
		//		Vector2 velocity = rb->GetVelocity();
		//		velocity.y = -550.0f;

		//		rb->SetVelocity(velocity);
		//		rb->SetGround(false);
		//		sonic_Pos = sonicTr->GetPos();
		//	
		//		sonicTr->SetPos(sonic_Pos);
		//	}
		//}
	}
	void Callapses::OnCollisionStay(Collider* other)
	{
	}
	void Callapses::OnCollisionExit(Collider* other)
	{
	}
	void Callapses::idle()
	{
	}
	void Callapses::death()
	{
	}
}
