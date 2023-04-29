#include "Boss_trash.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "Rigidbody.h"


namespace jk
{
	Boss_trash::Boss_trash(Gameobject* owner)
	{
		mOwner = owner;
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"END_BG", L"..\\Resources\\END_BG.bmp");


		mAnimator->CreateAnimation(L"END_Boss_trash", mImage, Vector2{ 1408,99 }, Vector2{ 40,24 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"END_Boss_trash", false);
		

		//mRigidbody = AddComponent<Rigidbody>();
		//mRigidbody->SetMass(1.f);
	}
	Boss_trash::~Boss_trash()
	{
	}
	void Boss_trash::Initialize()
	{
		Gameobject::Initialize();
	}
	void Boss_trash::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		pos.y += 150 * Time::DeltaTime();
		tr->SetPos(pos);

		Gameobject::Update();
	}
	void Boss_trash::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Boss_trash::Release()
	{
		Gameobject::Release();
	}
	void Boss_trash::move()
	{
	}
	void Boss_trash::death()
	{
	}
	void Boss_trash::complete_bomb()
	{
	}
}
