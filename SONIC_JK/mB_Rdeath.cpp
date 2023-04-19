#include "mB_Rdeath.h"
#include "jk_Time.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "Rigidbody.h"

namespace jk
{
	mB_Rdeath::mB_Rdeath(Gameobject* owner)
	{
		mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"R_mBDeatht", mImage, Vector2{ 451.f,351.f }, Vector2{ 80.f,64.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"R_mBDeatht", false);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetGravity(Vector2{ 0.f,1.f });

	}
	mB_Rdeath::~mB_Rdeath()
	{
	}
	void mB_Rdeath::Initialize()
	{
		Gameobject::Initialize();
	}
	void mB_Rdeath::Update()
	{
		Gameobject::Update();
	}
	void mB_Rdeath::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void mB_Rdeath::Release()
	{
		Gameobject::Release();
	}
	void mB_Rdeath::OnCollisionEnter(Collider* other)
	{
	}
	void mB_Rdeath::OnCollisionStay(Collider* other)
	{
	}
	void mB_Rdeath::OnCollisionExit(Collider* other)
	{
	}
	void mB_Rdeath::death()
	{
	}
}