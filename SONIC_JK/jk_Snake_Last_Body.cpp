#include "jk_Snake_Last_Body.h"

#include "jk_Snake.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Snake_Third_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	Snake_Last_Body::Snake_Last_Body(Snake_Third_Body* set)
		: mBody_3(set)
		, mCurPos()
		, tr(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, snake_body_state()
	{
	}
	Snake_Last_Body::Snake_Last_Body()
		: mBody_3()
		, mCurPos()
		, tr(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, snake_body_state()
	{
	}
	Snake_Last_Body::~Snake_Last_Body()
	{
		//prevPositions.empty();
	}
	void Snake_Last_Body::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_mTaIl", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_mTaIl", mImage, Vector2{ 206.f,443.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_mTaIl", mImage, Vector2{ 72.f,443.f }, Vector2{ 16.f,16.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });
		mAnimator->Play(L"RSnake_mTaIl", true);

		tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Snake_Last_Body::Update()
	{
		Body3_State = mBody_3->Get_Snake_state();
		if (GetLife() == true)
		{
			mCurPos = mBody_3->Gepos(); 
		}


		switch (mState)
		{
		case jk::Snake_Last_Body::eSnake::Right:
			right();
			break;

		case jk::Snake_Last_Body::eSnake::Left:
			left();
			break;


		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_Last_Body::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Last_Body::Release()
	{
		Gameobject::Release();
	}
	void Snake_Last_Body::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Last_Body::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Last_Body::OnCollisionExit(Collider* other)
	{
	}

	void Snake_Last_Body::right()
	{
		tr->SetPos(Vector2(mCurPos.x - 130.f, mCurPos.y ));
		mAnimator->Play(L"LSnake_mTaIl", true);
		if (Body3_State == Snake_Third_Body::eSnake::Left)
		{	
			mCurPos = mBody_3->GetteurnPOs();
			tr->SetPos(Vector2(mCurPos.x + 130.f, mCurPos.y ));

			mState = eSnake::Left;
		}
	}
	void Snake_Last_Body::left()
	{
		tr->SetPos(Vector2(mCurPos.x + 130.f, mCurPos.y));
		mAnimator->Play(L"RSnake_mTaIl", true);
		if (Body3_State == Snake_Third_Body::eSnake::Right)
		{		
			mCurPos = mBody_3->GetteurnPOs();
			tr->SetPos(Vector2(mCurPos.x - 130.f, mCurPos.y ));

			mState = eSnake::Left;
		}
	}

}
