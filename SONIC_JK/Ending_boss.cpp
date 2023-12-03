#include "Ending_boss.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Time.h"


namespace jk
{
	Ending_boss::Ending_boss(Gameobject* owner)
		: mOwner(owner)
		, mAnimator(nullptr)
		, mImage(nullptr)
		, pos(0.f,0.f)
	{		
		mAnimator = AddComponent<Animator>();
		mImage = Resources::Load<Image>(L"END_BG", L"..\\Resources\\END_BG.bmp");
		mAnimator->CreateAnimation(L"END_Boss", mImage, Vector2{ 1408,43 }, Vector2{ 48,48 }, Vector2{ 0,0 }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->Play(L"END_Boss", false);
	}
	Ending_boss::~Ending_boss()
	{
	}
	void Ending_boss::Initialize()
	{
		Gameobject::Initialize();
	}
	void Ending_boss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos =tr->GetPos();		
		pos.y += 150 * Time::DeltaTime();
		tr->SetPos(pos);
		Gameobject::Update();
	}
	void Ending_boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Ending_boss::Release()
	{
		Gameobject::Release();
	}
}