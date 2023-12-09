#include "jk_Item_super.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"



namespace jk
{
	Item_super::Item_super(Gameobject* owner)
		: mOwner(owner)
		, Itemcheck(1)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, itemmState(eState::Idle)
		, sonicState()
	{
	}
	Item_super::~Item_super()
	{
	}
	void Item_super::Initialize()
	{
		mImage = Resources::Load<Image>(L"Item", L"..\\Resources\\Item.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"super_Item", mImage, Vector2(456, 131), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"ItemDeath", mImage, Vector2(460, 216), Vector2(32, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"super_Item", true);
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 85.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
		Gameobject::Initialize();
	}
	void Item_super::Update()
	{
		Gameobject::Update();
	}
	void Item_super::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Item_super::Release()
	{
		Gameobject::Release();
	}
	void Item_super::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			sonicState = sonic->Getsonicstate();

			if (sonicState == Sonic::eSonicState::Dash || sonicState == jk::Sonic::eSonicState::Jump || sonicState == jk::Sonic::eSonicState::Spin)
			{
				mAnimator->Play(L"ItemDeath", true);
				Itemcheck = 0;
			}
		}
	}
	void Item_super::OnCollisionStay(Collider* other)
	{
	}
	void Item_super::OnCollisionExit(Collider* other)
	{
	}
	void Item_super::CreateBlending()
	{
	}
	void Item_super::idle()
	{
	}
	void Item_super::death()
	{
	}
}