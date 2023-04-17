#include "jk_EmeraldSonic.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"


namespace jk
{
	EmeraldSonic::EmeraldSonic()
		: mState(eState::Idle)
		, mAnimator(nullptr)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 575.0f, 525.0f });
	}

	EmeraldSonic::~EmeraldSonic()
	{

	}

	void EmeraldSonic::Initialize()
	{
	/*	Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 575.0f, 525.0f });*/
		Image* mImage = Resources::Load<Image>(L"SONIC", L"..\\Resources\\sonic.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"sonicidle", mImage, Vector2(675,2328), Vector2(50, 55), Vector2(2, 2), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"sonicwalk", mImage, Vector2(725, 2328), Vector2(50, 55), Vector2(2, 2), 4, 2, 8, Vector2::Zero, 0.08);
		
		
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 150.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.0f) * size.x, (-0.3f) * size.y });// 콜라이더 생성위치 설정 필요
																			//(다른 오브젝트생성시에도 이렇게해야 충돌발생안함)
		Gameobject::Initialize();
	}

	void EmeraldSonic::Update()
	{
		Gameobject::Update();

		switch (mState)
		{
		case EmeraldSonic::eState::Idle:
			idle();
			break;

		case EmeraldSonic::eState::Move:
			move();
			break;

		default:
			break;
		}
	}

	void EmeraldSonic::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void EmeraldSonic::Release()
	{
		Gameobject::Release();
	}

	void EmeraldSonic::idle()
	{
		mAnimator->Play(L"sonicidle", true);
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState = eState::Move;
			mAnimator->Play(L"sonicwalk", true);
		}
	}

	void EmeraldSonic::move()
	{
		
	}

	void EmeraldSonic::jump()
	{
	}
}