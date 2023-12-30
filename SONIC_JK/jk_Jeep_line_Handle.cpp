#include "jk_Jeep_line_Handle.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Object.h"
#include "jk_Time.h"
#include "jk_Image.h"

#include "jk_SONIC.h"


namespace jk
{
	Jeep_line_Handle::Jeep_line_Handle()
		: mCenterpos(Vector2(0.f, 0.f))
		, mJeepline_state()
		, mDir_x(1)
		, mAngle(45)
		, mImage(nullptr)
		, mAnimator(nullptr)
	{
	}
	Jeep_line_Handle::~Jeep_line_Handle()
	{
	}
	void Jeep_line_Handle::Initialize()
	{
		mImage = Resources::Load<Image>(L"Jeep_line_Head", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Jeep_line_Head", mImage, Vector2(73, 562), Vector2(24, 8), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);

		mAnimator->Play(L"Jeep_line_Head", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(72.0f, 45.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.1f) * size.x, (-0.35f) * size.y });
		Gameobject::Initialize();
	}


	void Jeep_line_Handle::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		float centerX = mCenterpos.x;
		float centerY = mCenterpos.y;
		float radius = 210.0;

		if (mDir_x == 1)
		{
			mAngle += 10 * static_cast<float>(Time::DeltaTime()) * 10.f;
			if (mAngle > 135)
			{
				mDir_x = -1;
			}
		}
		else if (mDir_x == -1)
		{
			mAngle -= 10 * static_cast<float>(Time::DeltaTime()) * 10.f;
			if (mAngle < 45)
			{
				mDir_x = 1;
			}
		}

		float radian = mAngle * 3.14f / 180.0f;

		float x = centerX + radius * cos(radian);
		float y = centerY + radius * sin(radian);
		pos.x = x;
		pos.y = y;


		if (mAngle >= 45 && mAngle < 55)//¿À¸¥ÂÊ
		{
			mJeepline_state = 9;
		}

		if (mAngle >= 55 && mAngle < 65)
		{
			mJeepline_state = 8;
		}

		if (mAngle >= 65 && mAngle < 75)
		{
			mJeepline_state = 7;
		}

		if (mAngle >= 75 && mAngle < 85)
		{
			mJeepline_state = 6;
		}

		if (mAngle >= 85 && mAngle < 95)//Áß¾Ó
		{
			mJeepline_state = 5;
		}

		if (mAngle >= 95 && mAngle < 105)
		{
			mJeepline_state = 4;
		}

		if (mAngle >= 105 && mAngle < 115)
		{
			mJeepline_state = 3;
		}


		if (mAngle >= 115 && mAngle < 125)
		{
			mJeepline_state = 2;
		}


		if (mAngle >= 125 && mAngle < 135)//¿ÞÂÊ
		{
			mJeepline_state = 1;
		}


		tr->SetPos(pos);

		Gameobject::Update();
	}



	void Jeep_line_Handle::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Jeep_line_Handle::Release()
	{
		Gameobject::Release();
	}


	void Jeep_line_Handle::OnCollisionEnter(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true);
	}

	void Jeep_line_Handle::OnCollisionStay(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Collider* mSonic_Col = mSonic->GetComponent<Collider>();
		Vector2 mSonic_Pos = mSonic_Col->Getpos();
		Collider* Jeep_line_Col = this->GetComponent<Collider>();
		Vector2 Jeep_line_Pos = Jeep_line_Col->Getpos();
		Transform* sonicTr = mSonic->GetComponent<Transform>();
		Transform* grTr = this->GetComponent<Transform>();
		Vector2 sonic_Pos = sonicTr->GetPos();


		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{

			if (!((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt)))
			{
				sonic_Pos = pos;
				sonicTr->SetPos(sonic_Pos);
			}
			else
			{
				rb->SetGround(false);
				Vector2 velocity = rb->GetVelocity();
				velocity.x += 20.f;
				velocity.y -= 30.f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
				sonic_Pos = sonicTr->GetPos();
				sonic_Pos = sonic_Pos + Vector2{ 10.f ,-15.f };
				sonicTr->SetPos(sonic_Pos);
			}
		}
	}
	void Jeep_line_Handle::OnCollisionExit(Collider* other)
	{
	}
}
