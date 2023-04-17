#include "jk_Titlesonic.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_TitleSN.h"


namespace jk
{
	Titlesonic::Titlesonic()
		: mDir(0)
		//, mState(eState::Idle)
		, bTurn(false)
		, turnindex(0)
	{
	}
	Titlesonic::~Titlesonic()
	{
	}

	void Titlesonic::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 160.0f, 232.0f });	
		tr->SetScale(Vector2{ 1.3f, 1.2f });
		mImage = Resources::Load<Image>(L"Opening_BG", L"..\\Resources\\OPEN_BG.bmp");
		mAnimator->CreateAnimation(L"TitleBegin", mImage, Vector2(8, 472), Vector2(328, 232), Vector2(8, 8), 4, 4, 16, Vector2::Zero, 0.1);
		
		mImage = Resources::Load<Image>(L"Titlesonic_BG", L"..\\Resources\\OPEN_BG2.bmp");
		mAnimator->CreateAnimation(L"TitleSonic", mImage, Vector2(8, 936), Vector2(328, 232), Vector2(8, 8), 4, 2, 8, Vector2::Zero, 0.1);
		

		mAnimator->Play(L"TitleBegin", false);				
		mAnimator->GetCompleteEvent(L"TitleBegin") = std::bind(&Titlesonic::startscene, this);
		//mAnimator->GetEndEevent(L"TitleBegin") = std::bind(&Titlesonic::startscene, this);


		Gameobject::Initialize();
	}

	void Titlesonic::Update()
	{
		Gameobject::Update();
		/*switch (mState)
		{
		case Titlesonic::eState::Idle:
			idle();
			break;	

		case Titlesonic::eState::Move:
			move();
			break;
		default:
			break;
		}*/
	}

	void Titlesonic::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Titlesonic::Release()
	{
		Gameobject::Release();
	}

	void Titlesonic::startscene()
	{		
		Scene* curScene = SceneManager::GetActiveScene();
		TitleSN* TCN = new TitleSN();
		TCN->GetComponent<Transform>()->SetPos(Vector2(300.0f, 505.0f));
		curScene->AddGameobeject(TCN, jk_LayerType::Player);
		mAnimator->Play(L"TitleSonic", true);
	}

	//void Titlesonic::idle()
	//{
	//	Animation* activeAnim = mAnimator->GetActiveAnimation();
	//	int spriteIndex = activeAnim->Getspriteindex();
	//	if (spriteIndex == 15)
	//	{
	//		mState = eState::Move;
	//		
	//		turnindex = spriteIndex;
	//	}
	//}
	//void Titlesonic::move()
	//{
	//	
	//}
}



