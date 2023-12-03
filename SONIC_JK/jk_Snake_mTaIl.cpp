#include "jk_Snake_mTaIl.h"
#include "jk_Snake_body2.h"
#include "jk_Snake.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Object.h"

namespace jk
{
	Snake_mTaIl::Snake_mTaIl()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eSnake::Right)
		, bodyend_state()
		, snake_body(nullptr)
		, prevPos(0.f,0.f)
	{
	}
	Snake_mTaIl::~Snake_mTaIl()
	{
	}
	void Snake_mTaIl::Initialize()
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
		Gameobject::Initialize();
	}
	void Snake_mTaIl::Update()
	{
		prevPos = GetComponent<Transform>()->GetPos();
		switch (mState)
		{
		case jk::Snake_mTaIl::eSnake::Right:
			right();
			break;

		case jk::Snake_mTaIl::eSnake::Left:
			left();
			break;

		case jk::Snake_mTaIl::eSnake::Deth:
			deth();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_mTaIl::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_mTaIl::Release()
	{
		Gameobject::Release();
	}
	void Snake_mTaIl::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_mTaIl::OnCollisionStay(Collider* other)
	{
	}
	void Snake_mTaIl::OnCollisionExit(Collider* other)
	{
	}
	Vector2 Snake_mTaIl::GetPrevPos()
	{
		return prevPos;
	}
	void Snake_mTaIl::right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = snake_body->GetPrevPos() - Vector2{ 30.0f, 20.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_body2* body_end = dynamic_cast<Snake_body2*>(snake_body);
		bodyend_state = body_end->Get_Snake_state();
		if (bodyend_state == Snake_body2::eSnake::Left)
		{
			mAnimator->Play(L"LSnake_mTaIl", true);
			mState = eSnake::Left;
		}
		if (body_end->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}
	}
	void Snake_mTaIl::left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = snake_body->GetPrevPos() + Vector2{ 30.0f,-20.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_body2* body_end = dynamic_cast<Snake_body2*>(snake_body);
		bodyend_state = body_end->Get_Snake_state();
		if (bodyend_state == Snake_body2::eSnake::Right)
		{
			mAnimator->Play(L"RSnake_mTaIl", true);
			mState = eSnake::Right;
		}
		if (body_end->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}
	}
	void Snake_mTaIl::deth()
	{
		jk::object::Destory(this);
	}
}
