#include "boss1_object.h"
#include "boss_come.h"
#include "boss1_body.h"
#include "act6_bullet1.h"

#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "Rigidbody.h"
#include "jk_Ground.h"




namespace jk
{
	boss1_object::boss1_object()
		:mDir(1)
		, attack_check(1)
		, time(0)
		, attack_lotation(0)
		, Death_point(0)
		, pos(0.f,0.f)
		, bullet_check(0)
	{
		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"boss1_idle_ob", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_OPEN", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_CLOSE", mImage, Vector2{ 665,453 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);

	}

	boss1_object::~boss1_object()
	{
	}

	void boss1_object::Initialize()
	{
		Gameobject::Initialize();
	}



	void boss1_object::Update()
	{

		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();		


		if (Death_point == 1)
		{
			object::Destory(this);
		}

		if (Death_point == 0)
		{
			switch (mState)
			{
			case jk::boss1_object::eBossState::Idle:idle();
				break;

			case jk::boss1_object::eBossState::Up:up();
				break;

			case jk::boss1_object::eBossState::Down:down();
				break;

			default:
				break;
			}
		}


		Gameobject::Update();
	}


	void boss1_object::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}


	void boss1_object::Release()
	{
		Gameobject::Release();
	}


	void boss1_object::OnCollisionEnter(Collider* other)
	{

	}


	void boss1_object::OnCollisionStay(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
			rb->SetGround(true);	
	

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
				sonic_Pos.y = groundCol->Getpos().y ;				
				sonicTr->SetPos(sonic_Pos);
			}

			else
			{
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -550.0f;

				rb->SetVelocity(velocity);
				rb->SetGround(false);

				sonic_Pos = sonicTr->GetPos();			
				sonicTr->SetPos(sonic_Pos);

			}
		}
	}


	void boss1_object::OnCollisionExit(Collider* other)
	{
	}


	void boss1_object::idle()
	{

		if (mDir == 1)
		{
			mState = eBossState::Up;
			mAnimator->Play(L"Boss1_OPEN", false);

			Collider* collider = AddComponent<Collider>();
			collider->SetSize(Vector2(144.0f, 60.0f));
			Vector2 size = collider->GetSize();
			collider->SetCenter(Vector2{ (-0.18f) * size.x, (-0.85f) * size.y });
		}
		else if(mDir ==0)
		{
			mState = eBossState::Down;
			mAnimator->Play(L"Boss1_CLOSE", false);

			Collider* collider = GetComponent<Collider>();
			collider->SetSize(Vector2(0.f, 0.0f));			
		}
	}


	void boss1_object::up()
	{
		if (attack_lotation == 0)
		{
			if (attack_check == 1)
			{

				mAnimator->GetCompleteEvent(L"Boss1_OPEN") = std::bind(&boss1_object::attack_up, this);
				attack_check = -1;
				mDir = 0;
				

			}

			else if (attack_check == -1)
			{
			
					mAnimator->GetCompleteEvent(L"Boss1_OPEN") = std::bind(&boss1_object::attack_down, this);
					attack_check = 1;
					mDir = 0;
					
			}

			attack_lotation = 1;
		}
		
	}


	void boss1_object::down()
	{
		time += Time::DeltaTime();
		if (time >= 3)
		{

			mState = eBossState::Idle;		
			time = 0;
			mDir = 1;		
			attack_lotation = 0;
		}
	}

	void boss1_object::attack_up()
	{
		if (bullet_check == 0)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			act6_bullet1* bullet = new act6_bullet1();
			bullet->SetName(L"bullet_boss1");
			bullet->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 52.f, pos.y - 100.f });
			bullet->SetGroundImage(mGroundImage);

			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);

			//bullet->GetComponent<Rigidbody>()->AddForce(Vector2{ -50.f,-50.f });
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -550.f,-80.f });
			bullet->GetComponent<Rigidbody>()->SetGround(false);
	
			bullet_check = 1;
		}
		time += Time::DeltaTime();
		if (time >= 3)
		{
			mState = eBossState::Idle;
			time = 0;
			bullet_check = 0;

		}
	}

	void boss1_object::attack_down()
	{
		if (bullet_check == 0)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			act6_bullet1* bullet = new act6_bullet1();
			bullet->SetName(L"bullet_boss1");
			bullet->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 52.f, pos.y + 50 });
			bullet->SetGroundImage(mGroundImage);
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);

			//bullet->GetComponent<Rigidbody>()->AddForce(Vector2{ -50.f,0.f });
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -550.f,0.f });
			bullet->GetComponent<Rigidbody>()->SetGround(false);

			bullet_check = 1;
		}


		time += Time::DeltaTime();
		if (time >= 3)
		{
			mState = eBossState::Idle;
			time = 0;
			bullet_check = 0;
		}
	}
}