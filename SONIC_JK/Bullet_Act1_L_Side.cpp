#include "Bullet_Act1_L_Side.h"
#include "jk_Transform.h"
#include "jk_Time.h"
#include "jk_Boss.h"
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
	Bullet_Act1_L_Side::Bullet_Act1_L_Side(Gameobject* owner)
		: mCenterpos(Vector2(750.0f, 151.0f))
		, mCurpos(Vector2(0.0f, 0.0f))
		, mMonspeed(50.0f)
		, mMonmaxdistance(800.0f)
		, mDir(-1)
	{
		mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Bullet_Act1_L_Side", mImage, Vector2(1465, 146), Vector2(48, 32), Vector2(0, 8), 1, 2, 2, Vector2::Zero, 0.1f);
		mAnimator->Play(L"Bullet_Act1_L_Side", true);



		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(96.0f, 144.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });
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
		Sonic = mOwner->GetComponent<Transform>()->GetPos();


		tr->SetPos(pos);

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