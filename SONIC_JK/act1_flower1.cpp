#include "act1_flower1.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Animator.h"


namespace jk
{
	act1_flower1::act1_flower1()
		: mAnimator(nullptr)
		, mImage(nullptr)
	{
	}
	act1_flower1::~act1_flower1()
	{
	}
	void act1_flower1::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"act1_flower1", L"..\\Resources\\act1_flower.bmp");
		mAnimator->CreateAnimation(L"act1_flower2", mImage, Vector2(26, 1), Vector2(24, 48), Vector2(8, 0), 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->Play(L"act1_flower2", true);
		Gameobject::Initialize();
	}
	void act1_flower1::Update()
	{
		Gameobject::Update();
	}
	void act1_flower1::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act1_flower1::Release()
	{
		Gameobject::Release();
	}
	void act1_flower1::OnCollisionEnter(Collider* other)
	{
	}
	void act1_flower1::OnCollisionStay(Collider* other)
	{
	}
	void act1_flower1::OnCollisionExit(Collider* other)
	{
	}
}
