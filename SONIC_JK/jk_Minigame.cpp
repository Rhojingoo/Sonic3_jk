#include "jk_Minigame.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"


namespace jk
{
	Minigame::Minigame()
		: mDir(0)
		, mState(eState::Idle)
		, bTurn(false)
		, turnindex(0)
	{
	}
	Minigame::~Minigame()
	{
	}
	void Minigame::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();		
		tr->SetPos(Vector2{ 164.0f, 204.0f });
		tr->SetScale(Vector2{ 1.3f, 1.5f });
		mImage = Resources::Load<Image>(L"Emerald_Game_BG", L"..\\Resources\\Emerald_BG.bmp");				
		mAnimator->CreateAnimation(L"StageBegin", mImage, Vector2(24, 246), Vector2(328, 204), Vector2(8, 8), 1, 1, 1, Vector2::Zero, 0.2);
		mAnimator->CreateAnimation(L"StageWalk", mImage, Vector2(24,246), Vector2(328, 204), Vector2(8, 8), 4, 1, 16, Vector2::Zero, 0.1);
				
		Image* mImage1 = Resources::Load<Image>(L"Emerald_Game1_BG", L"..\\Resources\\EmeraldTurn_BG.bmp");
		mAnimator->CreateAnimation(L"LT_Lwhite", mImage1, Vector2(24, 246), Vector2(328, 204), Vector2(8, 8), 4, 2, 7, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"LT_Lblack", mImage1, Vector2(24, 654), Vector2(328, 204), Vector2(8, 8), 4, 2, 7, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RT_Lblack", mImage1, Vector2(24, 1062), Vector2(328, 204), Vector2(8, 8), 4, 2, 7, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"RT_Lwhite", mImage1, Vector2(24, 1470), Vector2(328, 204), Vector2(8, 8), 4, 2, 7, Vector2::Zero, 0.1);

		Gameobject::Initialize();
	}

	void Minigame::Update()
	{
		Gameobject::Update();
		switch (mState)
		{
		case Minigame::eState::Idle:
			idle();
			break;
		case Minigame::eState::Move:
			move();
			break;
		case Minigame::eState::Turn:
			turn();
			break;

		default:
			break;
		}
	}

	void Minigame::Render(HDC hdc)
	{
		Gameobject::Render(hdc);		
	}

	void Minigame::Release()
	{
		Gameobject::Release();
	}

	void Minigame::idle()
	{
		mAnimator->Play(L"StageBegin", true);
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState = eState::Move;
			mAnimator->Play(L"StageWalk", true);
		}
	}
	void Minigame::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();		
		Animation* activeAnim = mAnimator->GetActiveAnimation();
		int spriteIndex = activeAnim->Getspriteindex();
			
			
		if (spriteIndex == 8 &&( Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
		{						
				mDir = -1;
				mState = eState::Turn;
				mAnimator->Play(L"LT_Lblack", false);			
				turnindex = spriteIndex;			
		}
		else if (spriteIndex == 0 && (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT)))
		{
			if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKey(eKeyCode::LEFT))
			{
				mDir = -1;
				mState = eState::Turn;
				mAnimator->Play(L"LT_Lwhite", false);
				turnindex = spriteIndex;
			}
		}
		else if (spriteIndex == 8 &&( Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
		{
				mDir = 1;
				mState = eState::Turn;
				mAnimator->Play(L"RT_Lblack", false);
				turnindex = spriteIndex;
		}
		else if (spriteIndex == 0 && (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::RIGHT)))
		{
				mDir = 1;
				mState = eState::Turn;
				mAnimator->Play(L"RT_Lwhite", false);			
				turnindex = spriteIndex;
		}
			tr->SetPos(pos);
	}

	void Minigame::turn()
	{
		Animation* activeAnim = mAnimator->GetActiveAnimation();
		int spriteIndex = activeAnim->Getspriteindex();
		if (activeAnim->IsComplete())
		{
			mAnimator->Play(L"StageWalk", true);
			activeAnim = mAnimator->GetActiveAnimation();
			mState = eState::Move;
			if ((mDir == -1) && turnindex == 8)
			{
				activeAnim->Setspriteindex(0);
			}
			else if ((mDir == -1) && turnindex == 0)
			{
				activeAnim->Setspriteindex(8);
			}

			else if ((mDir == 1) && turnindex == 8)
			{
				activeAnim->Setspriteindex(0);
			}
			else if ((mDir == 1) && turnindex == 0)
			{
				activeAnim->Setspriteindex(8);
			}
		}
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();
		//tr->SetPos(pos);
	}
}


