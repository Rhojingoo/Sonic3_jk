#include "jk_Snake_Tail.h"
#include "jk_Snake.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Snake_Last_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	Snake_Tail::Snake_Tail(Snake_Last_Body* set)
		: mBody_end(set)
		, mCurPos(0.f, 0.f)
		, tr(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, Tail_state()
	{
	}
	Snake_Tail::Snake_Tail()
		: mBody_end(nullptr)
		, mCurPos(0.f, 0.f)
		, tr(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, Tail_state()
	{
	}
	Snake_Tail::~Snake_Tail()
	{
	}
	void Snake_Tail::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_Tail_End", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_end", mImage, Vector2{ 230.f,443.f }, Vector2{ 8.f,8.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_end", mImage, Vector2{ 96.f,443.f }, Vector2{ 8.f,8.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });
		mAnimator->Play(L"RSnake_end", true);

		tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Snake_Tail::Update()
	{

		Body_State = mBody_end->Get_Snake_state();
		if (GetLife() == true)
		{
			mCurPos = mBody_end->Gepos();
		}



		switch (mState)
		{
		case jk::Snake_Tail::eSnake::Right:
			right();
			break;

		case jk::Snake_Tail::eSnake::Left:
			left();
			break;



		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_Tail::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Tail::Release()
	{
		Gameobject::Release();
	}
	void Snake_Tail::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Tail::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Tail::OnCollisionExit(Collider* other)
	{
	}

	void Snake_Tail::right()
	{
		tr->SetPos(Vector2(mCurPos.x - 135.f, mCurPos.y - 10.f));

		if (Body_State == Snake_Last_Body::eSnake::Left)
		{
			
			mCurPos = mBody_end->GetteurnPOs();
			tr->SetPos(Vector2(mCurPos.x + 135.f, mCurPos.y - 10.f));
			mAnimator->Play(L"LSnake_end", true);
			mState = eSnake::Left;
		}

	}
	void Snake_Tail::left()
	{
		tr->SetPos(Vector2(mCurPos.x + 135.f, mCurPos.y + 10.f));
		if (Body_State == Snake_Last_Body::eSnake::Right)
		{
			
			mCurPos = mBody_end->GetteurnPOs();
			tr->SetPos(Vector2(mCurPos.x - 135.f, mCurPos.y + 10.f));
			mAnimator->Play(L"RSnake_end", true);
			mState = eSnake::Right;
		}
	}


}
