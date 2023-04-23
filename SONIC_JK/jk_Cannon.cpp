#include "jk_Cannon.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_SONIC.h"
#include "SonicState.h"
#include "jk_Canon_Bullet.h"
#include "jk_animal.h"
#include "jk_object.h"
#include "Rigidbody.h"
#include "jk_Ground.h"

int check_ground_CN = 0;

namespace jk
{
	Cannon::Cannon(Gameobject* owner)
		: mCurpos(Vector2(0.0f, 0.0f))
		, mDir(-1)
		, mOwner(owner)
		, sonicpattern(0)
		//, mCenterpos(Vector2(12280.0f, 3111.0f))
	{
	}
	Cannon::~Cannon()
	{
	}//4150,748
	void Cannon::Initialize()
	{
		mImage = Resources::Load<Image>(L"CANON", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RCannon", mImage, Vector2{ 24.f,353.f }, Vector2{ 52.f,63.f }, Vector2{ 4.f,0.f }, 5, 1, 5, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LCannon", mImage, Vector2{ 24.f,287.f }, Vector2{ 52.f,63.f }, Vector2{ 4.f,0.f }, 5, 1, 5, Vector2::Zero, 0.5f);

		mImage1 = Resources::Load<Image>(L"Effect", L"..\\Resources\\Effect.bmp");
		mAnimator->CreateAnimation(L"Canon_death", mImage1, Vector2{ 242.f,458.f }, Vector2{ 40.f,32.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);
		mAnimator->CreateAnimation(L"Canon_death2", mImage1, Vector2{ 242.f,498.f }, Vector2{ 32.f,24.f }, Vector2{ 8.f,0.f }, 4, 1, 4, Vector2::Zero, 0.3f);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(135.0f, 155.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });
		mAnimator->Play(L"LCannon", true);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
		
		Gameobject::Initialize();
	}
	void Cannon::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

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

		Transform* Canon_TR = GetComponent<Transform>();
		Rigidbody* Canon_rb = GetComponent<Rigidbody>();
		
		check_map = check->Get_map_check();

		mGroundImage = check->GetGroundImage();
		mGroundImage2 = check->GetGroundImage2();


		if (check_map == 0)
		{
			if (Canon_TR && Canon_rb && mGroundImage)
			{
				Vector2 Canon_ps = Canon_TR->GetPos();
				COLORREF FootColor = mGroundImage->GetPixel(Canon_ps.x, Canon_ps.y + 130);
				if (FootColor == RGB(0, 0, 0))
				{
					COLORREF FootColor = mGroundImage->GetPixel(Canon_ps.x, Canon_ps.y + 130);

					while (FootColor == RGB(0, 0, 0))
					{
						Canon_ps.y -= 1;
						FootColor = mGroundImage->GetPixel(Canon_ps.x, Canon_ps.y + 130);
						Canon_TR->SetPos(Canon_ps);
						Canon_rb->SetGround(true);
						check_ground_CN = 1;
					}
				}
			}
		}

		else if (check_map == 1)
		{
			if (Canon_TR && Canon_rb && mGroundImage2)
			{
				Vector2 Canon_ps = Canon_TR->GetPos();
				COLORREF FootColor = mGroundImage2->GetPixel(Canon_ps.x, Canon_ps.y + 130);
				if (FootColor == RGB(0, 0, 0))
				{
					COLORREF FootColor = mGroundImage2->GetPixel(Canon_ps.x, Canon_ps.y + 130);

					while (FootColor == RGB(0, 0, 0))
					{
						Canon_ps.y -= 1;
						FootColor = mGroundImage2->GetPixel(Canon_ps.x, Canon_ps.y + 130);
						Canon_TR->SetPos(Canon_ps);
						Canon_rb->SetGround(true);
					}
				}
				else
				{
					Canon_rb->SetGround(false);
				}

			}
		}


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

			//switch (sonicState) // if문대시 switch문으로 
			//{
			//case jk::Sonic::eSonicState::Dash:
			//case jk::Sonic::eSonicState::Jump:
			//case jk::Sonic::eSonicState::Spin:
			//{
			//	mAnimator->Play(L"Canon_death2", true);
			//	mAnimator->GetCompleteEvent(L"Canon_death2") = std::bind(&Cannon::death, this);
			//	break;
			//}
			//default:
			//	break;
			//}
			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAnimator->Play(L"Canon_death2", true);
				mAnimator->GetCompleteEvent(L"Canon_death2") = std::bind(&Cannon::death, this);
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
		mAnimator->GetCompleteEvent(L"RCannon") = std::bind(&Cannon::throw_CompleteEvent, this);
		mDir = 1;
	}
	void Cannon::left()
	{
		mAnimator->GetCompleteEvent(L"LCannon") = std::bind(&Cannon::throw_CompleteEvent, this);
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
		Rigidbody* bullet_rb = GetComponent<Rigidbody>();
		Image* groundImage = check->GetGroundImage();

		if (mDir == -1)
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Canon_Bullet* bullet = new Canon_Bullet(this);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y - 25 });
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ -300.0f, -300.0f });
			bullet->SetGroundImage(groundImage);
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
		}
		else
		{
			Scene* curScene = SceneManager::GetActiveScene();
			Canon_Bullet* bullet = new Canon_Bullet(this);
			bullet->GetComponent<Transform>()->SetPos(Vector2{ tr->GetPos().x, tr->GetPos().y - 25 });
			bullet->GetComponent<Rigidbody>()->SetVelocity(Vector2{ 300.0f, -300.0f });
			bullet->SetGroundImage(groundImage);
			curScene->AddGameobeject(bullet, jk_LayerType::Bullet);
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
}