#include "jk_Snake_Second_Body.h"
#include "jk_Snake.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Snake_Head.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	Snake_Second_Body::Snake_Second_Body(Snake_Head* ob)
		: mBody_1(ob)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mCurPos(0.f, 0.f)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_Second_Body::Snake_Second_Body()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mCurPos(0.f, 0.f)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_Second_Body::~Snake_Second_Body()
	{
	}
	void Snake_Second_Body::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_body1", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_body_Second", mImage, Vector2{ 182.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_body_Second", mImage, Vector2{ 48.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->Play(L"RSnake_body_Second", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });

		tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Snake_Second_Body::Update()
	{

		Body1_State = mBody_1->Get_Snake_state();
		if (GetLife() == true)
		{			
			mCurPos=mBody_1->Gepos();
		}

		switch (mState)
		{
		case jk::Snake_Second_Body::eSnake::Right:
			right();
			break;

		case jk::Snake_Second_Body::eSnake::Left:
			left();			
			break;
	

		default:
			break;
		}
		Gameobject::Update();
	}



	void Snake_Second_Body::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Second_Body::Release()
	{
		Gameobject::Release();
	}

	void Snake_Second_Body::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Second_Body::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Second_Body::OnCollisionExit(Collider* other)
	{
	}


	void Snake_Second_Body::right()
	{
		tr->SetPos(Vector2(mCurPos.x - 60.f, mCurPos.y +10.f));

		if (Body1_State == Snake_Head::eSnake::Left)
		{
			tr->SetPos(Vector2(mCurPos.x + 60.f, mCurPos.y - 10.f));
			mAnimator->Play(L"LSnake_body_Second", true);
			mState = eSnake::Left;
		}
	}
	void Snake_Second_Body::left()
	{
		tr->SetPos(Vector2(mCurPos.x + 60.f, mCurPos.y -10.f));

		if (Body1_State == Snake_Head::eSnake::Right)
		{
			tr->SetPos(Vector2(mCurPos.x - 60.f, mCurPos.y + 10.f));
			mAnimator->Play(L"RSnake_body_Second", true);
			mState = eSnake::Right;
		}
	}

}
