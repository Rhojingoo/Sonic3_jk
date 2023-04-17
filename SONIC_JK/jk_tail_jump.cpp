#include "jk_tail_jump.h"
#include "jk_Tails.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
//#include "yaBaseBullet.h"
#include "jk_Scene.h"
#include "jk_BaseBullet.h"
#include "jk_Ground.h"
#include "Rigidbody.h"
#include "jk_Monster.h"
#include "jk_BaseBullet.h"
#include "jk_Object.h"


namespace jk
{
	tail_jump::tail_jump(Gameobject* owner, int dir, int falling)
		:mDir(dir)
		,mFalling(falling)
	{
		mOwner = owner;

		Image* mImage = Resources::Load<Image>(L"RTails", L"..\\Resources\\RTails.bmp");
		Image* mImage1 = Resources::Load<Image>(L"LTails", L"..\\Resources\\LTails.bmp");

		mAnimator->CreateAnimation(L"RTailJPUP", mImage, Vector2(314, 264), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RTailJPDW", mImage, Vector2(443, 154), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailJPUP", mImage1, Vector2(314, 264), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LTailJPDW", mImage1, Vector2(443, 154), Vector2(58, 56), Vector2(4, 0), 4, 1, 4, Vector2::Zero, 0.1);

		mAnimator = AddComponent<Animator>();


		Gameobject::Update();
		mTails = mOwner->GetComponent<Transform>()->GetPos();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();


		//if (mDir == 1 && mFalling == 0)
		//{
		//	mAnimator->Play(L"RTailJPUP", true);
		//	pos = mTails;
		//}
		//else if (mDir == 1 && mFalling == 1)
		//{
		//	mAnimator->Play(L"RTailJPDW", true);
		//	pos = mTails;
		//}
		//else if (mDir == -1 && mFalling == 0)
		//{
		//	mAnimator->Play(L"LTailJPUP", true);
		//	pos = mTails;
		//}
		//else if (mDir == -1 && mFalling == 1)
		//{
		//	mAnimator->Play(L"LTailJPDW", true);
		//	pos = mTails;
		//}
		//tr->SetPos(Vector2{ pos });
	}



	tail_jump::~tail_jump()
	{
	}

	void tail_jump::Initialize()
	{
		Gameobject::Initialize();
	}

	void tail_jump::Update()
	{





		if (Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
			object::Destory(this);
		
	}

	void tail_jump::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void tail_jump::Release()
	{
		Gameobject::Release();
	}
}