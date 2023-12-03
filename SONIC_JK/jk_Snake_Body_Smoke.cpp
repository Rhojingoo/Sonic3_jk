#include "jk_Snake_Body_Smoke.h"
#include "jk_Snake.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Object.h"


namespace jk
{
	Snake_Body_Smoke::Snake_Body_Smoke()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, prevPos(0.f,0.f)
		, Head_ch(nullptr)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_Body_Smoke::~Snake_Body_Smoke()
	{
	}
	void Snake_Body_Smoke::Initialize()
	{
		mImage = Resources::Load<Image>(L"Snake_body1", L"..\\Resources\\Monster2.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"RSnake_body1", mImage, Vector2{ 158.f,499.f }, Vector2{ 40.f,56.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"LSnake_body1", mImage, Vector2{ 24.f,499.f }, Vector2{ 40.f,56.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->Play(L"RSnake_body1", true);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(55.0f, 55.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.25f) * size.x, (-0.35f) * size.y });	

		Gameobject::Initialize();
	}
	void Snake_Body_Smoke::Update()
	{
		prevPos = Head_ch->GetComponent<Transform>()->GetPos();
		switch (mState)
		{
		case jk::Snake_Body_Smoke::eSnake::Right:
			right();
			break;

		case jk::Snake_Body_Smoke::eSnake::Left:
			left();
			break;

		case jk::Snake_Body_Smoke::eSnake::Deth:
			deth();
			break;

		default:
			break;
		}
		Gameobject::Update();
	}
	void Snake_Body_Smoke::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Snake_Body_Smoke::Release()
	{
		Gameobject::Release();
	}
	void Snake_Body_Smoke::OnCollisionEnter(Collider* other)
	{
	}
	void Snake_Body_Smoke::OnCollisionStay(Collider* other)
	{
	}
	void Snake_Body_Smoke::OnCollisionExit(Collider* other)
	{
	}
	Vector2 Snake_Body_Smoke::GetPrevPos()
	{
		return prevPos;
	}

	void Snake_Body_Smoke::right()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 Head_pos = Head_ch->GetComponent<Transform>()->GetPos();
		pos = Head_pos - Vector2{ 80.0f, 20.0f };
		tr->SetPos(pos);

		Snake* snake_head = dynamic_cast<Snake*>(Head_ch);
		Snake_State = snake_head->Get_Snake_state();

		if (Snake_State == Snake::eSnake::Left)
		{
			mAnimator->Play(L"LSnake_body1", true);
			mState = eSnake::Left;
		}
		if (snake_head->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}

	}
	void Snake_Body_Smoke::left()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 Head_pos = Head_ch->GetComponent<Transform>()->GetPos();
		pos = Head_pos + Vector2{ 45.0f, -20.0f };	
		tr->SetPos(pos);

		Snake* snake_head = dynamic_cast<Snake*>(Head_ch);
		Snake_State = snake_head->Get_Snake_state();
		if (Snake_State == Snake::eSnake::Right)
		{
			mAnimator->Play(L"RSnake_body1", true);
			mState = eSnake::Right;
		}
		Snake_State = snake_head->Get_Snake_state();
		if (snake_head->GetState() == eState::Death)
		{
			jk::object::Destory(this);
		}

	}

	void Snake_Body_Smoke::deth()
	{
		jk::object::Destory(this);
	}
}