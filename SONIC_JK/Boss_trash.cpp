#include "Boss_trash.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Object.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Input.h"


namespace jk
{
	Boss_trash::Boss_trash(Gameobject* owner)
		: mOwner(owner)
		, mAnimator(nullptr)
		, mImage(nullptr)
		, mPos(0.f,0.f)
	{
		mOwner = owner;
		mImage = Resources::Load<Image>(L"END_BG", L"..\\Resources\\END_BG.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"END_Boss_trash", mImage, Vector2{ 1408,99 }, Vector2{ 40,24 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"END_Boss_trash", false);		
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
		mPos = tr->GetPos();
		mPos.y += 150 * static_cast<int>(Time::DeltaTime());
		tr->SetPos(mPos);

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
}
