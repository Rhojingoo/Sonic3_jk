#include "Electsonic.h"
#include "jk_Sonic.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Ground.h"
#include "Rigidbody.h"
#include "jk_Object.h"

namespace jk
{
	Electsonic::Electsonic(Gameobject* owner)
	:mOwner(nullptr)
		,mSonic(0.0f,0.0f)
	{
		mOwner = owner;

		Image* mImage = Resources::Load<Image>(L"Elect", L"..\\Resources\\Shield.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"Elect", mImage, Vector2(372, 472), Vector2(56, 56), Vector2(8, 8), 3, 4, 12, Vector2::Zero, 0.05f);

		mSonic = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = mSonic;
	
		mAnimator->Play(L"Elect", true);
	}
	Electsonic::~Electsonic()
	{
	}
	void Electsonic::Initialize()
	{
		Gameobject::Initialize();
	}
	void Electsonic::Update()
	{
		Gameobject::Update();

		mSonic=mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(mSonic);
		

		//if (Input::GetKeyDown(eKeyCode::RIGHT)
		//	|| Input::GetKeyDown(eKeyCode::LEFT))
		//	object::Destory(this);

	}
	void Electsonic::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Electsonic::Release()
	{
		Gameobject::Release();
	}
}