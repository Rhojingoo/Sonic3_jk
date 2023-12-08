#include "jk_Spring_Left.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"

#include "jk_SONIC.h"
#include "jk_Tails.h"

namespace jk
{
	Spring_Left::Spring_Left()
		: Spring_mc(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eState::Down)
	{
	}
	Spring_Left::~Spring_Left()
	{
	}
	void Spring_Left::Initialize()
	{
		Spring_mc = Resources::Load<Sound>(L"Spring", L"..\\Resources\\Sound\\Sonic\\Spring.wav");

		mImage = Resources::Load<Image>(L"spring_Left", L"..\\Resources\\Effect.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"spring_left", mImage, Vector2(414, 545), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"spring_left2", mImage, Vector2(454, 545), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"spring_left", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(50.0f, 100.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (0.6f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}
	void Spring_Left::Update()
	{
		switch (mState)
		{

		case Spring_Left::eState::Down:
			down();
			break;

		case Spring_Left::eState::Up:
			up();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void Spring_Left::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Spring_Left::Release()
	{
		Gameobject::Release();
	}
	void Spring_Left::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 spike_pos = tr->GetPos();
	
		if (Sonic* msonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Vector2 sonic_pos = msonic->GetComponent<Transform>()->GetPos();
			sonic_pos.y = sonic_pos.y + 120;

			if (sonic_pos.y < spike_pos.y)
			{
			}
			else
			{
				Spring_mc->Play(false);
				mAnimator->Play(L"spring_left2", false);
				mState = eState::Up;
			}
		}

		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			Vector2 tails_pos = tails->GetComponent<Transform>()->GetPos();
			tails_pos.y = tails_pos.y + 120;

			if (tails_pos.y < spike_pos.y)
			{
			}
			else
			{
				Spring_mc->Play(false);
				mAnimator->Play(L"spring_left2", false);
				mState = eState::Up;
			}
		}
	}
	void Spring_Left::OnCollisionStay(Collider* other)
	{
	}
	void Spring_Left::OnCollisionExit(Collider* other)
	{
	}
	void Spring_Left::up()
	{
		mAnimator->Play(L"spring_left", false);
		mState = eState::Down;
		return;
	}
	void Spring_Left::down()
	{
	}
}
