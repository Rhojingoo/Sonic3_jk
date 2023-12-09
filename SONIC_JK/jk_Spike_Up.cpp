#include "jk_Spike_Up.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"

namespace jk
{
	Spike_Up::Spike_Up()
		: mImage(nullptr)
		, mAnimator(nullptr)
	{
	}
	Spike_Up::~Spike_Up()
	{
	}
	void Spike_Up::Initialize()
	{
		mImage = Resources::Load<Image>(L"Spike_up", L"..\\Resources\\Effect.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Spike_up", mImage, Vector2(24, 217), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Spike_up", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 90.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.1f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}
	void Spike_Up::Update()
	{
		Gameobject::Update();
	}
	void Spike_Up::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Spike_Up::Release()
	{
		Gameobject::Release();
	}
	void Spike_Up::OnCollisionEnter(Collider* other)
	{
	}
	void Spike_Up::OnCollisionStay(Collider* other)
	{
	}
	void Spike_Up::OnCollisionExit(Collider* other)
	{
	}
}