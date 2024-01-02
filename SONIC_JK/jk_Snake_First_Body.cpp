#include "jk_Snake_First_Body.h"
#include "jk_Snake.h"
#include "jk_Snake_Head.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Object.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	Snake_First_Body::Snake_First_Body(Snake_Head* _Head)
		: Snake::Snake(_Head)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mPrevPos(0.f, 0.f)
		, mCurPos(0.f, 0.f)
		, mHead_ch(_Head)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_First_Body::Snake_First_Body()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mPrevPos(0.f, 0.f)
		, mCurPos(0.f, 0.f)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_First_Body::~Snake_First_Body()
	{
		//prevPositions.empty();
	}
	void Snake_First_Body::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_body1", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_body1", mImage, Vector2{ 158.f,499.f }, Vector2{ 40.f,56.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_body1", mImage, Vector2{ 24.f,499.f }, Vector2{ 40.f,56.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->Play(L"RSnake_body1", true);


		//Collider* collider = AddComponent<Collider>();
		//collider->SetSize(Vector2(55.0f, 55.0f));
		//Vector2 size = collider->GetSize();
		//collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });
		tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Snake_First_Body::Update()
	{
		Head_state = mHead_ch->Get_Snake_state();
		if (GetLife() == true)
		{
			mCurPos = mHead_ch->Gepos();
		}

		switch (mState)
		{
		case jk::Snake_First_Body::eSnake::Right:
			right();
			break;

		case jk::Snake_First_Body::eSnake::Left:
			left();
			break;


		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_First_Body::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_First_Body::Release()
	{
		Gameobject::Release();
	}
	void Snake_First_Body::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_First_Body::OnCollisionStay(Collider* other)
	{
	}
	void Snake_First_Body::OnCollisionExit(Collider* other)
	{
	}

	void Snake_First_Body::right()
	{
		tr->SetPos(Vector2(mCurPos.x-70.f, mCurPos.y-20.f));
	
		if (Head_state == Snake_Head::eSnake::Left)
		{			
			mAnimator->Play(L"LSnake_body1", true);
			mState = eSnake::Left;
		}
	}
	void Snake_First_Body::left()
	{		
		tr->SetPos(Vector2(mCurPos.x + 35.f, mCurPos.y-15.f));

		if (Head_state == Snake_Head::eSnake::Right)
		{
			mAnimator->Play(L"RSnake_body1", true);
			mState = eSnake::Right;
		}
	}


}