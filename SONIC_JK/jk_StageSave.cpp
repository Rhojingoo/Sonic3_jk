#include "jk_StageSave.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "Rigidbody.h"

namespace jk
{
	StageSave::StageSave()
		: mState(eState::Idle)
		, mDir(1)
	{
	}

	StageSave::~StageSave()
	{
	}

	void StageSave::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(400.0f, 471.0f));

		mImage = Resources::Load<Image>(L"save", L"..\\Resources\\Stagesave.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"saveidle", mImage, Vector2(24, 196), Vector2(48, 72), Vector2(8, 8), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"save", mImage, Vector2(24, 196), Vector2(48, 72), Vector2(8, 8), 4, 4, 12, Vector2::Zero, 0.1);
		mAnimator->Play(L"saveidle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(85.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (0.0f) * size.x, (-0.35f) * size.y });

		//mRigidbody = AddComponent<Rigidbody>();
		//mRigidbody->SetMass(1.0f);

		Gameobject::Initialize();

	}

	void StageSave::Update()
	{
		Gameobject::Update();

		switch (mState)
		{
		case StageSave::eState::Idle:
			idle();
			break;

		case StageSave::eState::Move:
			move();
			break;

		default:
			break;
		}
	}

	void StageSave::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void StageSave::Release()
	{
		Gameobject::Release();
	}

	void StageSave::OnCollisionEnter(Collider* other)
	{
		mState = eState::Move;
		mAnimator->Play(L"save", true);
	}

	void StageSave::OnCollisionStay(Collider* other)
	{
	}

	void StageSave::OnCollisionExit(Collider* other)
	{
		mState = eState::Idle;
		mAnimator->Play(L"saveidle", true);
	}

	void StageSave::idle()
	{
	
	}
	void StageSave::move()
	{
		//mAnimator->Play(L"save", true);
	}

}