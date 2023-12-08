#include "boss_come.h"
#include "boss1_body.h"
#include "jk_Time.h"
#include "jk_Input.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Object.h"
#include "jk_Ground.h"


namespace jk
{
	boss_come::boss_come(Gameobject* owner)
		: mImage(nullptr)
		, mGroundImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, check(nullptr)
		, mState(eBossState::Move)
		, pos(0.f, 0.f)
		, check_map(0)
		, mDir(0)

	{
		mImage = Resources::Load<Image>(L"First_boss", L"..\\Resources\\ActBG_6\\BOSS\\First_boss.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"First_boss_run", mImage, Vector2{ 597,0 }, Vector2{ 68,56 }, Vector2{ 4,0 }, 3, 1, 3, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"First_boss_jump", mImage, Vector2{ 597,64 }, Vector2{ 46,45 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"First_boss_run", true);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
	}

	boss_come::~boss_come()
	{
	}

	void boss_come::Initialize()
	{
		Gameobject::Initialize();
	}

	void boss_come::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		switch (mState)
		{
		case jk::boss_come::eBossState::Move:move();
			break;

		case jk::boss_come::eBossState::Jump:jump();
			break;

		default:
			break;
		}

		Transform* Boss_TR = GetComponent<Transform>();
		Rigidbody* Boss_rb = GetComponent<Rigidbody>();


		check_map = check->Get_map_check();
		mGroundImage = check->GetGroundImage4();

		if (Boss_TR && Boss_rb && mGroundImage)
		{
			Vector2 Boss_ps = Boss_TR->GetPos();
			COLORREF FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Boss_ps.x), static_cast<int>(Boss_ps.y + 100.f)));
			if (FootColor == RGB(0.f, 0.f, 0.f))
			{
				COLORREF FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Boss_ps.x), static_cast<int>(Boss_ps.y + 100.f)));

				while (FootColor == RGB(0.f, 0.f, 0.f))
				{
					Boss_ps.y -= 1;
					FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(Boss_ps.x), static_cast<int>(Boss_ps.y + 100.f)));
					Boss_TR->SetPos(Boss_ps);
					Boss_rb->SetGround(true);
				}
			}
			else
			{
				Boss_rb->SetGround(false);
			}
		}
		Gameobject::Update();
	}

	void boss_come::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void boss_come::Release()
	{
		Gameobject::Release();
	}

	void boss_come::OnCollisionEnter(Collider* other)
	{
		if (boss1_body* robotnic = dynamic_cast<boss1_body*>(other->GetOwner()))
		{
			object::Destory(this);
		}
	}

	void boss_come::OnCollisionStay(Collider* other)
	{
	}

	void boss_come::OnCollisionExit(Collider* other)
	{
	}

	void boss_come::move()
	{
		mDir = -1;
		mRigidbody->SetVelocity(Vector2{ -300.f, mRigidbody->GetVelocity().y });

		if (pos.x <= 6470)
		{
			mState = eBossState::Jump;
			mRigidbody->SetVelocity(Vector2(-250.f, -450.f));
			mRigidbody->SetGround(false);
			mAnimator->Play(L"First_boss_jump", true);

			Collider* collider = AddComponent<Collider>();
			collider->SetSize(Vector2(138.f, 135.f));
			Vector2 size = collider->GetSize();
			collider->SetCenter(Vector2{ (-0.12f) * size.x, (-0.2f) * size.y });
		}
	}


	void boss_come::jump()
	{
	}
}
