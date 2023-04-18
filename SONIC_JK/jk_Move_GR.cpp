#include "jk_Move_GR.h"
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
	Move_GR::Move_GR()
		: mCenterpos(Vector2(0.0f, 0.0f))
	
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(100.0f)
		, mMonmaxdistance(200.0f)
		, mDir(1)
		, sonicpattern(0)
	{
	}
	Move_GR::~Move_GR()
	{
	}
	void Move_GR::Initialize()
	{
		mImage = Resources::Load<Image>(L"Rock_Platform2", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"small_gr", mImage, Vector2(660, 682), Vector2(64, 40), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"small_gr", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(192.0f, 120.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });		

		Gameobject::Initialize();
	}
	void Move_GR::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();
		mCurpos = pos;


		switch (mState)
		{
		case Move_GR::eState::Up:
			up();
			break;

		case Move_GR::eState::Down:
			down();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Move_GR::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Move_GR::Release()
	{
		Gameobject::Release();
	}

	void Move_GR::OnCollisionEnter(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true);	

	}
	void Move_GR::OnCollisionStay(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* mSonic_Col = mSonic->GetComponent<Collider>();
		Vector2 mSonic_Pos = mSonic_Col->Getpos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->Getpos();

		Transform* sonicTr = mSonic->GetComponent<Transform>();
		Transform* grTr = this->GetComponent<Transform>();
		Vector2 sonic_Pos = sonicTr->GetPos();

		//float fLen = fabs(mSonic_Pos.y - groundPos.y);
		//float fSize = groundCol->GetSize().y;

		//sonic_Pos.y = groundPos.y - groundCol->GetSize().y ;
		//sonicTr->SetPos(sonic_Pos);
	

	//	실험해볼것
		float fLen = fabs(sonic_Pos.y - groundPos.y);
		float fSize = (mSonic_Col->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			sonic_Pos.y -= (fSize - fLen) - 0.5f;
			sonicTr->SetPos(sonic_Pos);

			//if ((mSonic->Getsonicstate() == Sonic::eSonicState::Jump) || (mSonic->Getsonicstate() == Sonic::eSonicState::Hurt))
			//{
			//	Vector2 velocity = rb->GetVelocity();
			//	velocity.y -= 550.0f;
			//	//velocity.x += 80.0f;
			//	rb->SetVelocity(velocity);
			//	rb->SetGround(false);

			//	sonic_Pos = sonicTr->GetPos();
			//	//sonic_Pos = sonic_Pos + Vector2{ 350.f ,-350.f };
			//	sonicTr->SetPos(sonic_Pos);
			//}
		}
	}

	void Move_GR::OnCollisionExit(Collider* other)
	{
		Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner());
		if (mSonic == nullptr)
			return;

		Rigidbody* rb = mSonic->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}

	void Move_GR::up()
	{
		Transform* tr = GetComponent<Transform>();

		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist >= mMonmaxdistance)
		{
			mState = eState::Down;
			mDir *= -1;
		}
		tr->SetPos(pos);

	}
	void Move_GR::down()
	{
		Transform* tr = GetComponent<Transform>();


		fDist = mCenterpos.y - pos.y - mMonmaxdistance;
		pos.y += mMonspeed * static_cast<float>(Time::DeltaTime());

		if (fDist <= -mMonmaxdistance)
		{
			mState = eState::Up;
			mDir *= -1;
		}
		tr->SetPos(pos);
	}
}