#include "jk_Snake_body2.h"
#include "jk_Snake_Body.h"
#include "jk_Snake.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"


namespace jk
{
	Snake_body2::Snake_body2()
	{
	}
	Snake_body2::~Snake_body2()
	{
	}
	void Snake_body2::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_body2", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_body_third", mImage, Vector2{ 182.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_body_third", mImage, Vector2{ 48.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });
		mAnimator->Play(L"RSnake_body_third", true);
		Gameobject::Initialize();
	}
	void Snake_body2::Update()
	{
		prevPos = GetComponent<Transform>()->GetPos();
	
		switch (mState)
		{
		case jk::Snake_body2::eSnake::Right:
			right();
			break;

		case jk::Snake_body2::eSnake::Left:
			left();
			break;

		case jk::Snake_body2::eSnake::Deth:
			deth();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_body2::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_body2::Release()
	{
		Gameobject::Release();
	}
	void Snake_body2::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_body2::OnCollisionStay(Collider* other)
	{
	}
	void Snake_body2::OnCollisionExit(Collider* other)
	{
	}

	Vector2 Snake_body2::GetPrevPos()
	{
		return prevPos;
	}

	void Snake_body2::right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = snake_body->GetPrevPos() - Vector2{ 45.0f, 20.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_Body* snake_body1 = dynamic_cast<Snake_Body*>(snake_body);
		snake_body_state = snake_body1->Get_Snake_state();
		if (snake_body_state == Snake_Body::eSnake::Left)
		{
			mAnimator->Play(L"LSnake_body_third", true);
			mState = eSnake::Left;
		}
		if (snake_body1->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}


	}

	void Snake_body2::left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = snake_body->GetPrevPos() + Vector2{ 45.0f,-20.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_Body* snake_body1 = dynamic_cast<Snake_Body*>(snake_body);
		snake_body_state = snake_body1->Get_Snake_state();
		if (snake_body_state == Snake_Body::eSnake::Right)
		{
			mAnimator->Play(L"RSnake_body_third", true);
			mState = eSnake::Right;
		}
		if (snake_body1->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}
	}
	void Snake_body2::deth()
	{
		jk::object::Destory(this);
	} 
}