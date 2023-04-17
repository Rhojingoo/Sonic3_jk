#include "jk_ItemBigRing.h"
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

namespace jk
{
	ItemBigRing::ItemBigRing()
		: mState(eState::Idle)
		, mDir(1)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(15064.f, 3680.0f));
	}

	ItemBigRing::~ItemBigRing()
	{
	}

	void ItemBigRing::Initialize()
	{
		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(90.0f,471.0f));
		mImage = Resources::Load<Image>(L"sring", L"..\\Resources\\SpRing.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Spring", mImage, Vector2(24, 546), Vector2(66, 66), Vector2(2, 2), 4, 3, 12, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"EatLSpring", mImage, Vector2(24, 744), Vector2(66, 66), Vector2(2, 2), 4, 2, 7, Vector2::Zero, 0.1);
		mAnimator->Play(L"Spring", true);
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
		
		mAnimator->Play(L"EatLSpring", true);
		//mAnimator->GetCompleteEvent(L"EatLSpring");
		object::Destory(this);
		SceneManager::LoadScene(jk_SceneType::MiniGameplay);
		Camera::Clear();
			
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
}