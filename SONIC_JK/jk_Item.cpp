#include "jk_Item.h"
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

namespace jk
{
	Item::Item(Gameobject* owner)	
		:mOwner(owner)
		, Itemcheck(1)
	{		
		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(90.0f, 551.0f));
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		mImage = Resources::Load<Image>(L"Item", L"..\\Resources\\Item.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"FireItem", mImage, Vector2(528, 131), Vector2(32, 32), Vector2(0, 0), 1,1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ItemDeath", mImage, Vector2(460, 216), Vector2(32, 16), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"ElectItem", true);
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 85.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });
		Gameobject::Initialize();

	}
	void Item::Update()
	{
		switch (itemmState)
		{
		case Item::eState::Idle:
			idle();
			break;

		case Item::eState::Death:
			death();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Item::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Item::Release()
	{
		Gameobject::Release();
	}
	void Item::OnCollisionEnter(Collider* other)
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
	void Item::OnCollisionStay(Collider* other)
	{
	}
	void Item::OnCollisionExit(Collider* other)
	{
	}
	void Item::CreateBlending()
	{
	}
	void Item::idle()
	{
	}
	void Item::death()
	{
	}
}
