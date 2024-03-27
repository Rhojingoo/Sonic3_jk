#include "jk_Cannon.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_object.h"
#include "jk_Pixel_Ground.h"
#include "jk_Image.h"

#include "jk_Cannon_Bullet.h"
#include "jk_animal.h"
#include "jk_Sound.h"

int check_ground_CN = 0;

namespace jk
{
	Cannon::Cannon(Gameobject* owner)
		: mPos(0.f, 0.f)
		, mDir(-1)
		, mCheck_Map(0)
		, sonicState()
		, tailsState()
		, mState(eCannon::Idle)
		, mOwner(owner)
		, mPixel_Ground(nullptr)
		, mGroundImage(nullptr)
		, mGroundImage2(nullptr)
		, mDeath_Sound(nullptr)
		, mImage(nullptr)
		, mImage1(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mDeath(false)
		, mBullet(nullptr)
		, mBullet_tr(nullptr)
		, mBullet_rg(nullptr)

	{
	}
	Cannon::~Cannon()
	{
	}
	void Cannon::Initialize()
	{
		mDeath_Sound = Resources::Load<Sound>(L"Monster_Death", L"..\\Resources\\Sound\\Sonic\\Monster_Death.wav");

		mImage = Resources::Load<Image>(L"CANON", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RCannon", mImage, Vector2{ 24.f,353.f }, Vector2{ 52.f,63.f }, Vector2{ 4.f,0.f }, 5, 1, 5, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LCannon", mImage, Vector2{ 24.f,287.f }, Vector2{ 52.f,63.f }, Vector2{ 4.f,0.f }, 5, 1, 5, Vector2::Zero, 0.5f);

		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator->CreateAnimation(L"Canon_death", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Canon_death2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);


		mAnimator->Play(L"LCannon", true);
		mAnimator->GetCompleteEvent(L"Canon_death2") = std::bind(&Cannon::death, this);
		mAnimator->GetCompleteEvent(L"LCannon") = std::bind(&Cannon::throw_CompleteEvent, this);
		mAnimator->GetCompleteEvent(L"RCannon") = std::bind(&Cannon::throw_CompleteEvent, this);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(135.0f, 155.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });


		mBullet = new Cannon_Bullet(this);
		Scene* curScene = SceneManager::GetInitScene();
		mBullet_tr = mBullet->GetComponent<Transform>();
		mBullet_rg = mBullet->GetComponent<Rigidbody>();
		curScene->AddGameobeject(mBullet, jk_LayerType::Bullet);
		mBullet->SetState(eState::Pause);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();
	}

	void Cannon::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		Ground_check();

		switch (mState)
		{
		case jk::Cannon::eCannon::Idle:idle();
			break;

		case jk::Cannon::eCannon::Right:right();
			break;

		case jk::Cannon::eCannon::Left:left();
			break;

		case jk::Cannon::eCannon::Death:death();
			break;

		default:
			break;
		}

		Setpos_monster(mPos);
		Gameobject::Update();
	}
	void Cannon::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Cannon::Release()
	{
		Gameobject::Release();
	}


	void Cannon::OnCollisionEnter(Collider* other)
	{
		//if(other->GetOwner()->GetName() == L"Sonic") → name으로 찾아서 dynamic_cast보다 빠르게 접근가능할 수있다. ★확인필요(속도차이)★
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mDeath_Sound->Play(false);
				mAnimator->Play(L"Canon_death2", true);
			}
		}
		else if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			tailsState = tails->GetTails_state();

			if (tailsState == Tails::eTailsState::Dash || tailsState == Tails::eTailsState::Jump || tailsState == Tails::eTailsState::Spin || tailsState == Tails::eTailsState::Movejump)
			{
				mDeath_Sound->Play(false);
				mAnimator->Play(L"Canon_death2", true);
			}
		}
	}

	void Cannon::OnCollisionStay(Collider* other)
	{
	}

	void Cannon::OnCollisionExit(Collider* other)
	{
	}

	void Cannon::idle()
	{
		if (mDir == -1)
		{
			mState = eCannon::Left;
			mAnimator->Play(L"LCannon", false);
		}
		if (mDir == 1)
		{
			mState = eCannon::Right;
			mAnimator->Play(L"RCannon", false);
		}
	}

	void Cannon::right()
	{
		mDir = 1;
	}

	void Cannon::left()
	{
		mDir = -1;
	}

	void Cannon::death()
	{
		jk::object::Destory(this);

		Cannon::release_animal();
	}


	void Cannon::throw_CompleteEvent()
	{

		Transform* tr = GetComponent<Transform>();

		if (mDir == -1)
		{
			mBullet->SetState(eState::Active);
			mBullet_tr->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y - 25 });
			mBullet_rg->SetVelocity(Vector2{ 0.f, 0.f });
			mBullet_rg->SetVelocity(Vector2{ -300.0f, -300.0f });
		}
		else
		{
			mBullet->SetState(eState::Active);
			mBullet_tr->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y - 25 });
			mBullet_rg->SetVelocity(Vector2{ 0.f, 0.f });
			mBullet_rg->SetVelocity(Vector2{ 300.0f, -300.0f });
		}

		mDir = mDir * -1;
		mState = eCannon::Idle;
	}

	void Cannon::release_animal()
	{
		Transform* tr = GetComponent<Transform>();
		Scene* curScene = SceneManager::GetActiveScene();
		Animal* ani = new Animal(mOwner);

		ani->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y });
		curScene->AddGameobeject(ani, jk_LayerType::Animal);
	}
	void Cannon::Ground_check()
	{
		Transform* Canon_TR = GetComponent<Transform>();
		Rigidbody* Canon_rb = GetComponent<Rigidbody>();

		mCheck_Map = mPixel_Ground->Get_map_check();

		mGroundImage = mPixel_Ground->GetGroundImage();
		mGroundImage2 = mPixel_Ground->GetGroundImage2();

		Image* selectedImage = (mCheck_Map == 0) ? mGroundImage : mGroundImage2;

		if (Canon_TR && Canon_rb && mGroundImage)
		{
			Vector2 Canon_ps = Canon_TR->GetPos();
			COLORREF FootColor = selectedImage->GetPixel(static_cast<int>(Canon_ps.x), static_cast<int>(Canon_ps.y) + 130);
			if (FootColor == GROUNDCOLOR)
			{			
				while (FootColor == GROUNDCOLOR)
				{
					Canon_ps.y -= 1;
					FootColor = selectedImage->GetPixel(static_cast<int>(Canon_ps.x), static_cast<int>(Canon_ps.y) + 130);
					Canon_TR->SetPos(Canon_ps);
					Canon_rb->SetGround(true);
					check_ground_CN = 1;
				}
			}
		}
		mBullet->SetGroundImage(selectedImage);

	}
}