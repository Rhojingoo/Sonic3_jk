#include "jk_ItemBigRing.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Blending.h"
#include "jk_Object.h"
#include "jk_Camera.h"
#include "jk_SONIC.h"

namespace jk
{
	ItemBigRing::ItemBigRing()
		: mState(eState::Idle)
		, mImage(nullptr)
		, mAnimator(nullptr)
	{


	}

	ItemBigRing::~ItemBigRing()
	{
	}

	void ItemBigRing::Initialize()
	{
		mImage = Resources::Load<Image>(L"sring", L"..\\Resources\\SpRing.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Spring", mImage, Vector2(24, 546), Vector2(66, 66), Vector2(2, 2), 4, 3, 12, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"EatLSpring", mImage, Vector2(24, 744), Vector2(66, 66), Vector2(2, 2), 4, 2, 7, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Spring", true);
		mAnimator->GetCompleteEvent(L"EatLSpring") = std::bind(&ItemBigRing::death, this);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(180.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}

	void ItemBigRing::Update()
	{
		Gameobject::Update();

		switch (mState)
		{
		case ItemBigRing::eState::Idle:
			idle();
			break;

		case ItemBigRing::eState::Move:
			move();
			break;

		default:
			break;
		}
	}

	void ItemBigRing::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void ItemBigRing::Release()
	{
		Gameobject::Release();
	}

	void ItemBigRing::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			mAnimator->Play(L"EatLSpring", true);
		}
	}

	void ItemBigRing::OnCollisionStay(Collider* other)
	{
	}

	void ItemBigRing::OnCollisionExit(Collider* other)
	{
	}

	void ItemBigRing::CreateBlending()
	{
		object::Instantiate<Blending>(jk_LayerType::Blend);
	}

	void ItemBigRing::idle()
	{

	}

	void ItemBigRing::move()
	{

	}
	void ItemBigRing::death()
	{
		object::Destory(this);
		SceneManager::LoadScene(jk_SceneType::MiniGameplay);
		Camera::Clear();
	}
}