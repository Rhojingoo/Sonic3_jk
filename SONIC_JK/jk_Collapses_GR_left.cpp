#include "jk_Collapses_GR_left.h"
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

float time_Gr2 = 0.0f;
int check_Gr2 = 0;

namespace jk
{
	Collapses_GR_left::Collapses_GR_left()
	{
	}
	Collapses_GR_left::~Collapses_GR_left()
	{
	}

	void Collapses_GR_left::Initialize()
	{
		mImage = Resources::Load<Image>(L"Ground_collapses", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Ground_collapses_left", mImage, Vector2(540, 285), Vector2(96, 64), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"Ground_collapses_left", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(288.0f, 192.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}

	void Collapses_GR_left::Update()
	{
		switch (mState)
		{

		case Collapses_GR_left::eState::Idle:
			idle();
			break;

		case Collapses_GR_left::eState::Death:
			death();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}

	void Collapses_GR_left::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Collapses_GR_left::Release()
	{
		Gameobject::Release();
	}

	void Collapses_GR_left::OnCollisionEnter(Collider* other)
	{

	}

	void Collapses_GR_left::OnCollisionStay(Collider* other)
	{

			if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
			{
				Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
				rb->SetGround(true);
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();

				Collider* mSonic_Col = mSonic->GetComponent<Collider>();
				Vector2 mSonic_Pos = mSonic_Col->Getpos();
				Collider* groundCol = this->GetComponent<Collider>();
				Vector2 groundPos = groundCol->Getpos();
				Transform* sonicTr = mSonic->GetComponent<Transform>();
				Transform* grTr = this->GetComponent<Transform>();
				Vector2 sonic_Pos = sonicTr->GetPos();


				Vector2 velocity = rb->GetVelocity();
				velocity.y = 0.0f;
				rb->SetVelocity(velocity);


				if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
				{
					sonic_Pos.y = groundCol->Getpos().y - groundCol->GetSize().y / 2.f;
					check_Gr2 = 1;
					sonicTr->SetPos(sonic_Pos);
				}

				else
				{
					Vector2 velocity = rb->GetVelocity();
					velocity.y = -550.0f;

					rb->SetVelocity(velocity);
					rb->SetGround(false);

					sonic_Pos = sonicTr->GetPos();
					//sonic_Pos = sonic_Pos + Vector2{ 350.f ,-350.f };
					sonicTr->SetPos(sonic_Pos);

				}
			}
			if (check_Gr2 == 1)
			{
				time_Gr2 += Time::DeltaTime();
				if (time_Gr2 >= 3)
				{
					mState = eState::Death;
					jk::object::Destory(this);
					return;
				}
			}
		
	}

	void Collapses_GR_left::OnCollisionExit(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}

	void Collapses_GR_left::idle()
	{
	}

	void Collapses_GR_left::death()
	{		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Callapses* GR_callapese = new Callapses();
		Scene* curScene = SceneManager::GetActiveScene();
		curScene->AddGameobeject(GR_callapese, jk_LayerType::BG_props);
		GR_callapese->GetComponent<Transform>()->SetPos(pos);		
	}
}
