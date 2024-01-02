#include "jk_Snake_Third_Body.h"
#include "jk_Snake.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Snake_Second_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	Snake_Third_Body::Snake_Third_Body(Snake_Second_Body* ob)
		: mBody_2(ob)
		, mCurPos()
		, tr(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, snake_body_state()
	{
	}
	Snake_Third_Body::Snake_Third_Body()
		: mBody_2()
		, mCurPos()
		, tr(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, snake_body_state()
	{
	}
	Snake_Third_Body::~Snake_Third_Body()
	{
	}
	void Snake_Third_Body::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_body2", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_body_third", mImage, Vector2{ 182.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_body_third", mImage, Vector2{ 48.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->Play(L"RSnake_body_third", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });


		tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Snake_Third_Body::Update()
	{
	
		Body2_State = mBody_2->Get_Snake_state();
		if (GetLife() == true)
		{
			mCurPos = mBody_2->Gepos(); 
		}


		switch (mState)
		{
		case jk::Snake_Third_Body::eSnake::Right:
			right();
			break;

		case jk::Snake_Third_Body::eSnake::Left:
			left();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_Third_Body::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Third_Body::Release()
	{
		Gameobject::Release();
	}
	void Snake_Third_Body::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Third_Body::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Third_Body::OnCollisionExit(Collider* other)
	{
	}



	void Snake_Third_Body::right()
	{
		tr->SetPos(Vector2(mCurPos.x - 100.f, mCurPos.y - 10.f));

		if (Body2_State == Snake_Second_Body::eSnake::Left)
		{

			mCurPos = mBody_2->GetteurnPOs();
			tr->SetPos(Vector2(mCurPos.x + 100.f, mCurPos.y - 10.f));
			mAnimator->Play(L"LSnake_body_third", true);
			mState = eSnake::Left;
		}
	}

	void Snake_Third_Body::left()
	{
		tr->SetPos(Vector2(mCurPos.x + 100.f, mCurPos.y + 10.f));
		if (Body2_State == Snake_Second_Body::eSnake::Right)
		{
			
			mCurPos = mBody_2->GetteurnPOs();
			tr->SetPos(Vector2(mCurPos.x - 100.f, mCurPos.y + 10.f));
			mAnimator->Play(L"RSnake_body_third", true);
			mState = eSnake::Right;
		}

	}

	void Snake_Third_Body::deth()
	{
		jk::object::Destory(this);
	}
}