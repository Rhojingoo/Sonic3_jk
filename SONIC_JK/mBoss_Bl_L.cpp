#include "mBoss_Bl_L.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Object.h"


namespace jk
{
	mBoss_Bl_L::mBoss_Bl_L(Gameobject* owner)
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mOwner(owner)
	{
		mImage = Resources::Load<Image>(L"mBoss_shot", L"..\\Resources\\ActBG_1_2\\mBoss_shot.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"L_MB_sh", mImage, Vector2{ 440.f,0.f }, Vector2{142.f,36.f }, Vector2{ 0.f,4.f }, 1, 9, 9, Vector2::Zero, 0.05f);
		mAnimator->Play(L"L_MB_sh", false);
		mAnimator->GetCompleteEvent(L"L_MB_sh") = std::bind(&mBoss_Bl_L::death, this);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(426.0f, 96.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.25f) * size.y });
	}

	mBoss_Bl_L::~mBoss_Bl_L()
	{
	}

	void mBoss_Bl_L::Initialize()
	{
		Gameobject::Initialize();
	}

	void mBoss_Bl_L::Update()
	{
		//Transform* tr = GetComponent<Transform>();
		//Vector2 mPos = tr->GetPos();
		//Setpos_bullet(mPos);
		Gameobject::Update();
	}

	void mBoss_Bl_L::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void mBoss_Bl_L::Release()
	{
		Gameobject::Release();
	}

	void mBoss_Bl_L::OnCollisionEnter(Collider* other)
	{
	}

	void mBoss_Bl_L::OnCollisionStay(Collider* other)
	{
	}

	void mBoss_Bl_L::OnCollisionExit(Collider* other)
	{
	}
	void mBoss_Bl_L::death()
	{
		object::Destory(this);
	}
}