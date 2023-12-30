#include "jk_Spring_Up.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"

#include "jk_Image.h"
#include "jk_Sound.h"

#include "jk_SONIC.h"
#include "jk_Tails.h"


namespace jk
{
	Spring_Up::Spring_Up()
		: Spring_mc(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eState::Down)
	{
	}
	Spring_Up::~Spring_Up()
	{
	}
	void Spring_Up::Initialize()
	{
		Spring_mc = Resources::Load<Sound>(L"Spring", L"..\\Resources\\Sound\\Sonic\\Spring.wav");

		mImage = Resources::Load<Image>(L"spring_up", L"..\\Resources\\Effect.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"spring_up", mImage, Vector2(504, 497), Vector2(32, 40), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"spring_up2", mImage, Vector2(544, 497), Vector2(32, 40), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);

		mAnimator->Play(L"spring_up", false);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(100.0f, 40.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (0.35f) * size.y });
		Gameobject::Initialize();
	}
	void Spring_Up::Update()
	{
		switch (mState)
		{
		case Spring_Up::eState::Down:
			down();
			break;

		case Spring_Up::eState::Up:
			up();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void Spring_Up::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Spring_Up::Release()
	{
		Gameobject::Release();
	}
	void Spring_Up::OnCollisionEnter(Collider* other)
	{
		mAnimator->Play(L"spring_up2", false);
		mState = eState::Up;
		Spring_mc->Play(false);
	}
	void Spring_Up::OnCollisionStay(Collider* other)
	{
	}
	void Spring_Up::OnCollisionExit(Collider* other)
	{
	}
	void Spring_Up::up()
	{
		mAnimator->Play(L"spring_up", false);
		mState = eState::Down;
		return;
	}
	void Spring_Up::down()
	{
	}
}
