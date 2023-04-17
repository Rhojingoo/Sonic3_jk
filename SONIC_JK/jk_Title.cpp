#include "jk_Title.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Titlesonic.h"
#include "JK_TitleSN.h"
#include "jk_Object.h"



namespace jk
{
 
    Title::Title()
        : mDir(0)
        , mState(eState::Idle)
        , bTurn(false)
        , turnindex(0)
    {
    }

    Title::~Title()
    {
    }

    void Title::Initialize()
    {
        mAnimator = AddComponent<Animator>();
        Transform* tr = GetComponent<Transform>();
        tr->SetPos(Vector2{ 160.0f, 232.0f });
        tr->SetScale(Vector2{ 1.3f, 1.2f });
        Image* mImage1 = Resources::Load<Image>(L"TitleST", L"..\\Resources\\OPEN_BG2.bmp");
        mAnimator->CreateAnimation(L"TitleST", mImage1, Vector2(8, 8), Vector2(328, 232), Vector2(8, 8), 4, 2, 8, Vector2::Zero, 0.08);
        mAnimator->Play(L"TitleST", false);
        //컴플릿 쓸때사용
        //mAnimator->GetCompleteEvent(L"TitleST") = std::bind(&Titlesonic::startscene, this);


  

        Gameobject::Initialize();
    }

    void Title::Update()
    {
        Gameobject::Update();
        switch (mState)
        {
        case Title::eState::Idle:
            idle();
           // mAnimator->Play(L"TitleST", false);
            break; 

        default:
            break;
        }
    }
    void Title::Render(HDC hdc)
    {        
        Gameobject::Render(hdc);      
    }
      void Title::Release()
    {
        Gameobject::Release();
    }
    void Title::idle()
    {      

     /*   Animation* activeAnim = mAnimator->GetActiveAnimation();
        int spriteIndex = activeAnim->Getspriteindex();
        if (spriteIndex == 7)
        {
            mAnimator1->Play(L"TTSN", true);*/
           /* Instantiate<TitleSN>(jk_LayerType::Player);*/
        //}

    }

    void Title::move()
    {       
        //컴플릿쓸때 사용 (아이들상태에 서 실행하지 않고 이니셜때 상태사용필수)
        //Scene* curScene = SceneManager::GetActiveScene();
        //TitleSN* TCN = new TitleSN();
        //TCN->GetComponent<Transform>()->SetPos(Vector2(300.0f, 505.0f));
        //curScene->AddGameobeject(TCN, jk_LayerType::Player);
    }

}
