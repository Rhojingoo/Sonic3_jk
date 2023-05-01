#include "jk_Collapses_Ground.h"
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
#include "jk_Callapses.h"


float time_Gr = 0.0f; 
int check_Gr = 0;

namespace jk
{
	Collapses_Ground::Collapses_Ground()
	{
	}
	Collapses_Ground::~Collapses_Ground()
	{
	}
	void Collapses_Ground::Initialize()
	{
		mImage = Resources::Load<Image>(L"Ground_collapses", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Ground_collapses", mImage, Vector2(500, 562), Vector2(96, 64), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"Ground_collapses", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(288.0f, 192.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}
	void Collapses_Ground::Update()
	{
		switch (mState)
		{

		case Collapses_Ground::eState::Idle:
			idle();
			break;

		case Collapses_Ground::eState::Death:
			death();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void Collapses_Ground::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Collapses_Ground::Release()
	{
		Gameobject::Release();
	}
	void Collapses_Ground::OnCollisionEnter(Collider* other)
	{

	}

	void Collapses_Ground::OnCollisionStay(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);
			Collider* mSonic_Col = mSonic->GetComponent<Collider>();
			Vector2 mSonic_colPos = mSonic_Col->Getpos();		
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			Transform* grTr = this->GetComponent<Transform>();
			Collider* groundCol = this->GetComponent<Collider>();
			Vector2 ground_colPos = groundCol->Getpos();
			

			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);


			if(! ((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos.y =  groundCol->Getpos().y - groundCol->GetSize().y/2.f;
 				check_Gr = 1;
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
		if (check_Gr == 1)
		{
			time_Gr += Time::DeltaTime();
			if (time_Gr >= 1)
			{
				mState = eState::Death;				
				return;
			}
		}
	}

	void Collapses_Ground::OnCollisionExit(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}


	void Collapses_Ground::idle()
	{
	}


	void Collapses_Ground::death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Callapses* GR_callapese = new Callapses();
		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameobeject(GR_callapese, jk_LayerType::BG_props);		
		GR_callapese->GetComponent<Transform>()->SetPos(pos);

		jk::object::Destory(this);
		
	}
}