#include "Act1_2_Boss_wall.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "Rigidbody.h"
#include "jk_SONIC.h"


namespace jk
{
	Act1_2_Boss_wall::Act1_2_Boss_wall()
		:mCollider(nullptr)
	{
	}
	Act1_2_Boss_wall::~Act1_2_Boss_wall()
	{
	}
	void Act1_2_Boss_wall::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 3000.0f));		
		Transform* tr = GetComponent<Transform>();

		Gameobject::Initialize();		
	}

	void Act1_2_Boss_wall::Update()
	{
		Gameobject::Update();
	}

	void Act1_2_Boss_wall::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Act1_2_Boss_wall::Release()
	{
		Gameobject::Release();
	}

	void Act1_2_Boss_wall::OnCollisionEnter(Collider* other)
	{

	}
	void Act1_2_Boss_wall::OnCollisionStay(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = sonic->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Collider* mSonic_Col = sonic->GetComponent<Collider>();
			Vector2 mSonic_colPos = mSonic_Col->Getpos();
			Transform* sonicTr = sonic->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Transform* grTr = this->GetComponent<Transform>();
			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 ground_colPos = groundCol->Getpos();


			Vector2 velocity = rb->GetVelocity();
			velocity.x = 0.0f;
			rb->SetVelocity(velocity);


			if (!((sonic->Getsonicstate() == Sonic::eSonicState::Jump) || (sonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos.x = groundCol->Getpos().x;
				sonicTr->SetPos(sonic_Pos);
			}

			else
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -650.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				sonic_Pos = sonicTr->GetPos();
				sonicTr->SetPos(sonic_Pos);
			}
		}


	}
	void Act1_2_Boss_wall::OnCollisionExit(Collider* other)
	{
	}
	void Act1_2_Boss_wall::idle()
	{
	}
	void Act1_2_Boss_wall::death()
	{
	}
}