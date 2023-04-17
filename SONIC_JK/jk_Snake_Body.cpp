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
	Snake_Body::Snake_Body()
	{
	}
	Snake_Body::~Snake_Body()
	{
	}
	void Snake_Body::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_body1", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_body_Second", mImage, Vector2{ 182.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_body_Second", mImage, Vector2{ 48.f,443.f }, Vector2{ 16.f,24.f }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });
		mAnimator->Play(L"RSnake_body_Second", true);
		Gameobject::Initialize();
	}
	void Snake_Body::Update()
	{
		prevPos = GetComponent<Transform>()->GetPos();
		switch (mState)
		{
		case jk::Snake_Body::eSnake::Right:
			right();
			break;	
			
		case jk::Snake_Body::eSnake::Left:
			left();
			break;

		case jk::Snake_Body::eSnake::Deth:
			deth();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_Body::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Body::Release()
	{
		Gameobject::Release();
	}
	void Snake_Body::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Body::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Body::OnCollisionExit(Collider* other)
	{
	}
	Vector2 Snake_Body::GetPrevPos()
	{
		return prevPos;
	}

	void Snake_Body::right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Body_smoke->GetPrevPos() - Vector2{ 80.0f, 0.0f };// 포스 위치 변경	
		tr->SetPos(pos);

		Snake_Body_Smoke* snake_smoke_body = dynamic_cast<Snake_Body_Smoke*>(Body_smoke);
		Snake_State = snake_smoke_body->Get_Snake_state();
		if (Snake_State == Snake_Body_Smoke::eSnake::Left)
		{
			mAnimator->Play(L"LSnake_body_Second", true);
			mState = eSnake::Left;
		}

		if (snake_smoke_body->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}

	}
	void Snake_Body::left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Body_smoke->GetPrevPos() + Vector2{ 80.0f, 0.0f };// 포스 위치 변경	
		tr->SetPos(pos);
	

		Snake_Body_Smoke* snake_smoke_body = dynamic_cast<Snake_Body_Smoke*>(Body_smoke);
		Snake_State = snake_smoke_body->Get_Snake_state();
		if (Snake_State == Snake_Body_Smoke::eSnake::Right)
		{
			mAnimator->Play(L"RSnake_body_Second", true);
			mState = eSnake::Right;
		}
		if (snake_smoke_body->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}

	}
	void Snake_Body::deth()
	{
		jk::object::Destory(this);
		
	}
}
