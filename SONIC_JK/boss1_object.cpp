#include "boss1_object.h"


#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "Rigidbody.h"
#include "jk_Pixel_Ground.h"


#include "jk_Time.h"


namespace jk
{
	boss1_object::boss1_object(Gameobject* owner)
		: mDir(1)
		, time(0)
		, attack_lotation(0)
		, attack_check(1)
		, Death_point(0)
		, bullet_check(0)
		, pos(0.f, 0.f)
		, mState(eBossState::Idle)
		, boss(nullptr)
		, Bullet1(nullptr)
		, mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, bullet(nullptr)

	{
		boss = dynamic_cast<boss1_body*>(owner);

		Bullet1 = Resources::Load<Sound>(L"Bullet1", L"..\\Resources\\Sound\\Bullet1.wav");

		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"boss1_idle_ob", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 1, 1, 1, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_OPEN_Up", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_OPEN_Down", mImage, Vector2{ 665,509 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Boss1_CLOSE", mImage, Vector2{ 665,453 }, Vector2{ 52,48 }, Vector2{ 4,0 }, 4, 1, 4, Vector2::Zero, 0.3f);

		mAnimator->GetCompleteEvent(L"Boss1_OPEN_Up") = std::bind(&boss1_object::attack_up, this);
		mAnimator->GetCompleteEvent(L"Boss1_OPEN_Down") = std::bind(&boss1_object::attack_down, this);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(0.0f, 0.0f));
		Vector2 size = mCollider->GetSize();
		mCollider->SetCenter(Vector2{ (-0.18f) * size.x, (-0.85f) * size.y });


		Scene* curScene = SceneManager::GetActiveScene();
		bullet = new act6_bullet1();
		bullet->SetName(L"bullet_boss1");
		bullet->SetState(eState::Active);
		//bullet->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 52.f, pos.y + 50 });
		bullet->SetGroundImage(mGroundImage);
		curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
		bullet->SetState(eState::Pause);
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
		Death_point = boss->Get_BossDeath();


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

			Vector2 groundPos = mCollider->Getpos();
			Transform* sonicTr = mSonic->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();


			Vector2 velocity = rb->GetVelocity();
			velocity.y = 0.0f;
			rb->SetVelocity(velocity);

			if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos.y = mCollider->Getpos().y - mCollider->GetSize().y - 50;
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
			if (attack_check == 1)
			{
				mAnimator->Play(L"Boss1_OPEN_Up", false);
				attack_check = -1;
			}

			else if (attack_check == -1)
			{
				mAnimator->Play(L"Boss1_OPEN_Down", false);
				attack_check = 1;
			}

			mCollider->SetSize(Vector2(144.0f, 60.0f));
			Vector2 size = mCollider->GetSize();
			mCollider->SetCenter(Vector2{ (-0.18f) * size.x, (-0.85f) * size.y });
		}
		else if (mDir == 0)
		{
			mState = eBossState::Down;
			mAnimator->Play(L"Boss1_CLOSE", false);

			mCollider = GetComponent<Collider>();
			mCollider->SetSize(Vector2(0.f, 0.0f));
		}
	}


	void boss1_object::up()
	{
		if (attack_lotation == 0)
		{
			attack_lotation = 1;
		}
		if (bullet_check >= 1)
		{
			time += static_cast<float>(Time::DeltaTime());
			if (time >= 3)
			{
				mState = eBossState::Idle;
				time = 0;
				bullet_check = 0;
				mDir = 0;
			}
		}
	}
	void boss1_object::down()
	{
		time += static_cast<float>(Time::DeltaTime());
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
			Bullet1->Play(false);
			bullet->SetState(eState::Active);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 52.f, pos.y - 100.f });
			bullet->SetGroundImage(mGroundImage);
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -550.f,-150.f });
			bullet->GetComponent<Rigidbody>()->SetGround(false);

			bullet_check = 1;
		}
	}

	void boss1_object::attack_down()
	{
		if (bullet_check == 0)
		{
			Bullet1->Play(false);
			bullet->SetState(eState::Active);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ pos.x + 52.f, pos.y + 50 });
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -550.f,0.f });
			bullet->GetComponent<Rigidbody>()->SetGround(false);

			bullet_check = 1;
		}


		time += static_cast<int>(Time::DeltaTime());
		if (time >= 3)
		{
			mState = eBossState::Idle;
			time = 0;
			bullet_check = 0;
			mDir = 0;
		}
	}
}