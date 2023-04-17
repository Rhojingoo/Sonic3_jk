#include "jk_Snake_Tail_End.h"
#include "jk_Snake_body2.h"
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
	Snake_Tail_End::Snake_Tail_End()
	{
	}
	Snake_Tail_End::~Snake_Tail_End()
	{
	}
	void Snake_Tail_End::Initialize()
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
		Gameobject::Initialize();
	}
	void Snake_Tail_End::Update()
	{
		prevPos = GetComponent<Transform>()->GetPos();
		switch (mState)
		{
		case jk::Snake_Tail_End::eSnake::Right:
			right();
			break;

		case jk::Snake_Tail_End::eSnake::Left:
			left();
			break;

		case jk::Snake_Tail_End::eSnake::Deth:
			deth();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_Tail_End::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Tail_End::Release()
	{
		Gameobject::Release();
	}
	void Snake_Tail_End::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Tail_End::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Tail_End::OnCollisionExit(Collider* other)
	{
	}
	Vector2 Snake_Tail_End::GetPrevPos()
	{
		return prevPos;
	}
	void Snake_Tail_End::right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = snake_body->GetPrevPos() - Vector2{ 30.0f, 20.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_mTaIl* body_end = dynamic_cast<Snake_mTaIl*>(snake_body);
		Tail_state = body_end->Get_Snake_state();
		if (Tail_state == Snake_mTaIl::eSnake::Left)
		{
			mAnimator->Play(L"LSnake_end", true);
			mState = eSnake::Left;
		}
		if (body_end->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}
	}
	void Snake_Tail_End::left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = snake_body->GetPrevPos() + Vector2{ 30.0f,-20.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_mTaIl* body_end = dynamic_cast<Snake_mTaIl*>(snake_body);
		Tail_state = body_end->Get_Snake_state();
		if (Tail_state == Snake_mTaIl::eSnake::Right)
		{
			mAnimator->Play(L"RSnake_end", true);
			mState = eSnake::Right;
		}
		if (body_end->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}
	}
	void Snake_Tail_End::deth()
	{
		jk::object::Destory(this);

	}
}
