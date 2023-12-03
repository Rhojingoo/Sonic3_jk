#include "boss_bomber.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"








namespace jk
{
	boss_bomber::boss_bomber(Gameobject* owner)
		: mMonspeed(1650.0f)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, pos(0.f, 0.f)
	{
		mImage = Resources::Load<Image>(L"Act1_3_Boomber", L"..\\Resources\\ActBG_1_3\\Act1_3_Boomber.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Act1_3_Boomber", mImage, Vector2{ 24,198 }, Vector2{ 384,128 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Act1_3_Boomber", true);
	}

	boss_bomber::~boss_bomber()
	{
	}

	void boss_bomber::Initialize()
	{
		Gameobject::Initialize();
	}

	void boss_bomber::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();
		pos.x += mMonspeed * static_cast<float>(Time::DeltaTime());

		tr->SetPos(pos);
		Gameobject::Update();
	}

	void boss_bomber::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void boss_bomber::Release()
	{
		Gameobject::Release();
	}
	void boss_bomber::OnCollisionEnter(Collider* other)
	{
	}
	void boss_bomber::OnCollisionStay(Collider* other)
	{
	}
	void boss_bomber::OnCollisionExit(Collider* other)
	{
	}
}
