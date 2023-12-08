#include "jk_Ring.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"

#include "jk_Object.h"
#include "jk_SONIC.h"


namespace jk
{
	Ring::Ring(Gameobject* owner)
		: Ringcheck(0)
		, mOwner(owner)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, Ring_State(eState::Idle)
	{

	}

	Ring::~Ring()
	{
	}

	void Ring::Initialize()
	{
		mImage = Resources::Load<Image>(L"Ring", L"..\\Resources\\Ring.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Ring_turn", mImage, Vector2(128, 303), Vector2(20, 16), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"Ring_Eat", mImage, Vector2(128, 323), Vector2(20, 16), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Ring_turn", true);
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(65.0f, 60.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
		Ringcheck = 0;
		Gameobject::Initialize();
	}

	void Ring::Update()
	{
		Ringcheck;

		switch (Ring_State)
		{
		case Ring::eState::Idle:
			idle();
			break;

		case Ring::eState::Eat:
			eat();
			break;


		case Ring::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}

	void Ring::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Ring::Release()
	{
		Gameobject::Release();
	}

	void Ring::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mAnimator->Play(L"Ring_Eat", false);		
		
			Ring_State = eState::Eat;
		}
	}

	void Ring::OnCollisionStay(Collider* other)
	{
		
	}

	void Ring::OnCollisionExit(Collider* other)
	{
	}

	void Ring::CreateBlending()
	{
	}

	void Ring::idle()
	{
	}

	void Ring::eat()
	{
		mAnimator->GetCompleteEvent(L"Ring_Eat") = std::bind(&Ring::death, this);
		Ringcheck += 1;
	}

	void Ring::death()
	{
		object::Destory(this);	
	}

}