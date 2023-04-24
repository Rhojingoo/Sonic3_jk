#include "act1_flower2.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"

namespace jk
{
	act1_flower2::act1_flower2()
	{
	}
	act1_flower2::~act1_flower2()
	{
	}
	void act1_flower2::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();

		mImage = Resources::Load<Image>(L"act1_flower2", L"..\\Resources\\act1_flower.bmp");
		mAnimator->CreateAnimation(L"act1_flower2", mImage, Vector2(26, 113), Vector2(24, 24), Vector2(8, 0), 5, 1, 5, Vector2::Zero, 0.1);
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