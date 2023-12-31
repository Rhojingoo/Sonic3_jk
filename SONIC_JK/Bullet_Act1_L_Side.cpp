#include "Bullet_Act1_L_Side.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Time.h"
#include "jk_Image.h"
#include "jk_Animator.h"

namespace jk
{
	Bullet_Act1_L_Side::Bullet_Act1_L_Side(Gameobject* owner)
		: mOwner(owner)
		, mAnimator(nullptr)
		, mImage(nullptr)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Bullet_Act1_L_Side", mImage, Vector2(1465, 146), Vector2(48, 32), Vector2(0, 8), 1, 2, 2, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Bullet_Act1_L_Side", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(144.0f, 72.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.25f) * size.y });
		mOwner = owner;
	}

		Bullet_Act1_L_Side::~Bullet_Act1_L_Side()
	{
	}
	void Bullet_Act1_L_Side::Initialize()
	{
		Gameobject::Initialize();
	}
	void Bullet_Act1_L_Side::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		
		pos.x += 150.0f * static_cast<float>(Time::DeltaTime());
		tr->SetPos(pos);
		Setpos_bullet(pos);
		Gameobject::Update();
	}
	void Bullet_Act1_L_Side::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Bullet_Act1_L_Side::Release()
	{
		Gameobject::Release();
	}
}