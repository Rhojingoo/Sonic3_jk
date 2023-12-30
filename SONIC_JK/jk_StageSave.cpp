#include "jk_StageSave.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "Rigidbody.h"
#include "jk_Image.h"

namespace jk
{
	StageSave::StageSave()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
	}

	StageSave::~StageSave()
	{
	}

	void StageSave::Initialize()
	{
		mImage = Resources::Load<Image>(L"save", L"..\\Resources\\Stagesave.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"saveidle", mImage, Vector2(24, 196), Vector2(48, 72), Vector2(8, 8), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"save", mImage, Vector2(24, 196), Vector2(48, 72), Vector2(8, 8), 4, 4, 12, Vector2::Zero, 0.1f);
		mAnimator->Play(L"saveidle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(85.0f, 200.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (0.0f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}

	void StageSave::Update()
	{
		Gameobject::Update();
	}

	void StageSave::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void StageSave::Release()
	{
		Gameobject::Release();
	}

	void StageSave::OnCollisionEnter(Collider* other)
	{
		mAnimator->Play(L"save", true);
	}

	void StageSave::OnCollisionStay(Collider* other)
	{
	}

	void StageSave::OnCollisionExit(Collider* other)
	{
		mAnimator->Play(L"saveidle", true);
	}
}