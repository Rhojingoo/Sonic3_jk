#include "jk_Jeep_line.h"
#include "jk_Jeep_line_Handle.h"

#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"


namespace jk
{
	Jeep_line::Jeep_line(Gameobject* owner)
		:JL_State(5)
		, JL_Handle(nullptr)
		, mOwner(owner)
		, mState(eState::Jeep_Line5)
		, mImage(nullptr)
		, mAnimator(nullptr)
	{
	}
	Jeep_line::~Jeep_line()
	{
	}
	void Jeep_line::Initialize()
	{
		mImage = Resources::Load<Image>(L"Jeep_line", L"..\\Resources\\JEEP_LINE.bmp");
		mAnimator = AddComponent<Animator>();
		//45도
		mAnimator->CreateAnimation(L"Jeep_line9", mImage, Vector2(775, 358), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//55도
		mAnimator->CreateAnimation(L"Jeep_line8", mImage, Vector2(632, 358), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//65도
		mAnimator->CreateAnimation(L"Jeep_line7", mImage, Vector2(489, 358), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//75도
		mAnimator->CreateAnimation(L"Jeep_line6", mImage, Vector2(346, 358), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//85도
		mAnimator->CreateAnimation(L"Jeep_line5", mImage, Vector2(203, 276), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//95도
		mAnimator->CreateAnimation(L"Jeep_line4", mImage, Vector2(346, 276), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//105도
		mAnimator->CreateAnimation(L"Jeep_line3", mImage, Vector2(489, 276), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//115도
		mAnimator->CreateAnimation(L"Jeep_line2", mImage, Vector2(632, 276), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
		//125도
		mAnimator->CreateAnimation(L"Jeep_line1", mImage, Vector2(775, 276), Vector2(135, 76), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);
	
		mAnimator->Play(L"Jeep_line5", false);	
		

		Gameobject::Initialize();
	}



	void Jeep_line::Update()
	{
		JL_State = JL_Handle->Getjeepline_state();

		switch (mState)
		{
		case jk::Jeep_line::eState::Jeep_Line9:
			Jeep_line9();
			break;

		case jk::Jeep_line::eState::Jeep_Line8:
			Jeep_line8();
			break;

		case jk::Jeep_line::eState::Jeep_Line7:
			Jeep_line7();
			break;

		case jk::Jeep_line::eState::Jeep_Line6:
			Jeep_line6();
			break;

		case jk::Jeep_line::eState::Jeep_Line5:
			Jeep_line5();
			break;

		case jk::Jeep_line::eState::Jeep_Line4:
			Jeep_line4();
			break;

		case jk::Jeep_line::eState::Jeep_Line3:
			Jeep_line3();
			break;

		case jk::Jeep_line::eState::Jeep_Line2:
			Jeep_line2();
			break;

		case jk::Jeep_line::eState::Jeep_Line1:
			Jeep_line1();
			break;
	
		default:
			break;
		}

		Gameobject::Update();
	}


	void Jeep_line::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Jeep_line::Release()
	{
		Gameobject::Release();
	}
	void Jeep_line::OnCollisionEnter(Collider* other)
	{
	}
	void Jeep_line::OnCollisionStay(Collider* other)
	{
	}
	void Jeep_line::OnCollisionExit(Collider* other)
	{
	}

	void Jeep_line::Jeep_line9()
	{
		if (JL_State == 8)
		{
			mState = eState::Jeep_Line8;
			mAnimator->Play(L"Jeep_line8", true);
		}
	}
	void Jeep_line::Jeep_line8()
	{
		if (JL_State == 9)
		{
			mState = eState::Jeep_Line9;
			mAnimator->Play(L"Jeep_line9", true);
		}
		if (JL_State == 7)
		{
			mState = eState::Jeep_Line7;
			mAnimator->Play(L"Jeep_line7", true);
		}
	}
	void Jeep_line::Jeep_line7()
	{
		if (JL_State == 8)
		{
			mState = eState::Jeep_Line8;
			mAnimator->Play(L"Jeep_line8", true);
		}
		if (JL_State == 6)
		{
			mState = eState::Jeep_Line6;
			mAnimator->Play(L"Jeep_line6", true);
		}
	}
	void Jeep_line::Jeep_line6()
	{
		if (JL_State == 7)
		{
			mState = eState::Jeep_Line7;
			mAnimator->Play(L"Jeep_line7", true);
		}
		 if (JL_State == 5)
		{
			mState = eState::Jeep_Line5;
			mAnimator->Play(L"Jeep_line5", true);
		}
	}
	void Jeep_line::Jeep_line5()
	{
		if (JL_State == 6)
		{
			mState = eState::Jeep_Line6;
			mAnimator->Play(L"Jeep_line6", true);
		}
		if (JL_State == 4)
		{
			mState = eState::Jeep_Line4;
			mAnimator->Play(L"Jeep_line4", true);
		}
	}
	void Jeep_line::Jeep_line4()
	{
		if (JL_State == 5)
		{
			mState = eState::Jeep_Line5;
			mAnimator->Play(L"Jeep_line5", true);
		}
		if (JL_State == 3)
		{
			mState = eState::Jeep_Line3;
			mAnimator->Play(L"Jeep_line3", true);
		}
	}
	void Jeep_line::Jeep_line3()
	{
		if (JL_State == 4)
		{
			mState = eState::Jeep_Line4;
			mAnimator->Play(L"Jeep_line4", true);
		}
		if (JL_State == 2)
		{
			mState = eState::Jeep_Line2;
			mAnimator->Play(L"Jeep_line2", true);
		}
	}
	void Jeep_line::Jeep_line2()
	{
		if (JL_State == 3)
		{
			mState = eState::Jeep_Line3;
			mAnimator->Play(L"Jeep_line3", true);
		}
		if (JL_State == 1)
		{
			mState = eState::Jeep_Line1;
			mAnimator->Play(L"Jeep_line1", true);
		}
	}
	void Jeep_line::Jeep_line1()
	{
		if (JL_State == 2)
		{
			mState = eState::Jeep_Line2;
			mAnimator->Play(L"Jeep_line2", true);
		}
	}
}