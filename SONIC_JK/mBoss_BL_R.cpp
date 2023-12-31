#include "mBoss_BL_R.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "jk_Image.h"

namespace jk
{
	mBoss_BL_R::mBoss_BL_R(Gameobject* owner)
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mOwner(owner)
	{
		mImage = Resources::Load<Image>(L"mBoss_shot", L"..\\Resources\\ActBG_1_2\\mBoss_shot.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"L_MB_sh", mImage, Vector2{ 0.f,0.f }, Vector2{ 142.f,36.f }, Vector2{ 0.f,4.f }, 1, 9, 9, Vector2::Zero, 0.05f);
		mAnimator->Play(L"L_MB_sh", false);
		mAnimator->GetCompleteEvent(L"L_MB_sh") = std::bind(&mBoss_BL_R::death, this);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(426.0f, 96.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.2f) * size.x, (-0.25f) * size.y });
	}

	mBoss_BL_R::~mBoss_BL_R()
	{
	}

	void mBoss_BL_R::Initialize()
	{
		Gameobject::Initialize();
	}

	void mBoss_BL_R::Update()
	{		
		//Transform* mTr = GetComponent<Transform>();
		//Vector2 mPos = mTr->GetPos();
		//Setpos_bullet(mPos);
		Gameobject::Update();
	}

	void mBoss_BL_R::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void mBoss_BL_R::Release()
	{
		Gameobject::Release();
	}

	void mBoss_BL_R::OnCollisionEnter(Collider* other)
	{
	}

	void mBoss_BL_R::OnCollisionStay(Collider* other)
	{
	}

	void mBoss_BL_R::OnCollisionExit(Collider* other)
	{
	}
	void mBoss_BL_R::death()
	{
		object::Destory(this);
	}
}
