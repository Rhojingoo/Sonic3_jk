#include "act1_flower2.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Animator.h"
#include "jk_Resources.h"




namespace jk
{
	act1_flower2::act1_flower2()
		: mAnimator(nullptr)
		, mImage(nullptr)
	{
	}
	act1_flower2::~act1_flower2()
	{
	}
	void act1_flower2::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"act1_flower2", L"..\\Resources\\act1_flower.bmp");
		mAnimator->CreateAnimation(L"act1_flower2", mImage, Vector2(26, 113), Vector2(24, 24), Vector2(8, 0), 5, 1, 5, Vector2::Zero, 0.1f);
		mAnimator->Play(L"act1_flower2", true);
		Gameobject::Initialize();
	}
	void act1_flower2::Update()
	{
		Gameobject::Update();
	}
	void act1_flower2::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void act1_flower2::Release()
	{
		Gameobject::Release();
	}
	void act1_flower2::OnCollisionEnter(Collider* other)
	{
	}
	void act1_flower2::OnCollisionStay(Collider* other)
	{
	}
	void act1_flower2::OnCollisionExit(Collider* other)
	{
	}
}