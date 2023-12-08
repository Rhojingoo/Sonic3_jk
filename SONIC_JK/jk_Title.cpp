#include "jk_Title.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Animator.h"


namespace jk
{ 
    Title::Title()
        : mImage(nullptr)
        , mAnimator(nullptr)
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
        Image* mImage1 = Resources::Load<Image>(L"TitleST", L"..\\Resources\\Title\\OPEN_BG2.bmp");
        mAnimator->CreateAnimation(L"TitleST", mImage1, Vector2(8, 8), Vector2(328, 232), Vector2(8, 8), 4, 2, 8, Vector2::Zero, 0.08);
        mAnimator->Play(L"TitleST", false);  

        Gameobject::Initialize();
    }

    void Title::Update()
    {
        Gameobject::Update();
    }

    void Title::Render(HDC hdc)
    {        
        Gameobject::Render(hdc);      
    }

      void Title::Release()
    {
        Gameobject::Release();
    }
}
