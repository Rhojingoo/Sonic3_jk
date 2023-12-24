#include "jk_Snake_First_Body.h"
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
	Snake_First_Body::Snake_First_Body(Snake_Head* _Head)
		: mImage(nullptr)
		, mAnimator(nullptr)
		, prevPos(0.f, 0.f)
		, CurPos(0.f, 0.f)
		, Head_ch(_Head)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_First_Body::Snake_First_Body()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, prevPos(0.f, 0.f)
		, CurPos(0.f, 0.f)
		, Head_ch(_Head)
		, mState(eSnake::Right)
		, Snake_State()
	{
	}
	Snake_First_Body::~Snake_First_Body()
	{
	}
	void Snake_First_Body::Initialize()
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
		tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Snake_First_Body::Update()
	{
		Head_state = Head_ch->Get_Snake_state();
		if (GetLife() == true)
		{
			CurPos = Head_ch->GetNextPosition();
		}

		if (GetLife() == false)
			prevPositions.empty();

		prevPositions.push_back(CurPos);

		// 저장할 위치 수를 제한 (예: 몸통 길이에 따라)
		while (prevPositions.size() > 5) {
			prevPositions.pop_front();
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
		tr->SetPos(Vector2(CurPos.x-70.f, CurPos.y-20.f));
	
		if (Head_state == Snake_Head::eSnake::Left)
		{
			prevPositions.empty();
			mAnimator->Play(L"LSnake_body1", true);
			mState = eSnake::Left;
		}
	}
	void Snake_First_Body::left()
	{		
		tr->SetPos(Vector2(CurPos.x + 35.f, CurPos.y-15.f));

		if (Head_state == Snake_Head::eSnake::Right)
		{
			prevPositions.empty();	
			mAnimator->Play(L"RSnake_body1", true);
			mState = eSnake::Right;
		}
	}

	Vector2 Snake_First_Body::GetNextPosition()
	{
		if (!prevPositions.empty()) {
			Vector2 nextPos = prevPositions.front();
			prevPositions.pop_front();
			return nextPos;
		}
		return Vector2(); // 또는 오류 값 반환
	}
}