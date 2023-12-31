#include "mB_Ldeath.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Image.h"


jk::mB_Ldeath::mB_Ldeath(Gameobject* owner)
	: mImage(nullptr)
	, mAnimator(nullptr)
	, mOwner(owner)
{
	mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
	mAnimator = AddComponent<Animator>();
	mAnimator->CreateAnimation(L"L_mBDeatht", mImage, Vector2{ 451.f,331.f }, Vector2{ 80.f,64.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
	mAnimator->Play(L"L_mBDeatht", false);
}

jk::mB_Ldeath::~mB_Ldeath()
{
}

void jk::mB_Ldeath::Initialize()
{
	Gameobject::Initialize();
}

void jk::mB_Ldeath::Update()
{
	Gameobject::Update();
}

void jk::mB_Ldeath::Render(HDC hdc)
{
	Gameobject::Render(hdc);
}

void jk::mB_Ldeath::Release()
{
	Gameobject::Release();
}

void jk::mB_Ldeath::OnCollisionEnter(Collider* other)
{
}

void jk::mB_Ldeath::OnCollisionStay(Collider* other)
{
}

void jk::mB_Ldeath::OnCollisionExit(Collider* other)
{
}

void jk::mB_Ldeath::death()
{
}
