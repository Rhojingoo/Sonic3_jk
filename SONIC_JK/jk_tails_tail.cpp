#include "jk_tails_tail.h"
#include "jk_Tails.h"
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
	tails_tail::tails_tail(Gameobject* owner, int dir)
		:mDir(dir)		
	{
		mOwner = owner;

		Image* mImage = Resources::Load<Image>(L"RTails", L"..\\Resources\\RTails.bmp");
		Image* mImage1 = Resources::Load<Image>(L"LTails", L"..\\Resources\\LTails.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"RTailST", mImage, Vector2(24, 264), Vector2(54, 48), Vector2(4, 0), 5, 1, 5, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailST", mImage1, Vector2(24, 264), Vector2(54, 48), Vector2(4, 0), 5, 1, 5, Vector2::Zero, 0.1);

		mTails = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//pos = mTails;
	
		//if (mDir == 1)
		//{
		//	mAnimator->Play(L"RTailST", true);
		//	pos = mTails;
		//}
		//else if (mDir == -1)
		//{
		//	mAnimator->Play(L"LTailST", true);
		//	pos = mTails;
		//}
		//tr->SetPos(Vector2{ pos });
	}
	tails_tail::~tails_tail()
	{
	
	}
	void tails_tail::Initialize()
	{


		Gameobject::Initialize();

	}
	void tails_tail::Update()
	{	

		Gameobject::Update();

		if (Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		object::Destory(this);
		
		
	}

	void tails_tail::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void tails_tail::Release()
	{
		Gameobject::Release();
	}
}