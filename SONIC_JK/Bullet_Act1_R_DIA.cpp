#include "Bullet_Act1_R_DIA.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Time.h"


namespace jk
{
    Bullet_Act1_R_DIA::Bullet_Act1_R_DIA(Gameobject* owner)
        : mOwner(owner)
        , mAnimator(nullptr)
        , mImage(nullptr)
    {
        mImage = Resources::Load<Image>(L"ROBOT", L"..\\Resources\\ROBOT.bmp");
        mAnimator = AddComponent<Animator>();
        mAnimator->CreateAnimation(L"Bullet_Act1_R_DIA", mImage, Vector2(1367, 92), Vector2(48, 40), Vector2(8, 0), 4, 1, 4, Vector2::Zero, 0.1f);
        mAnimator->Play(L"Bullet_Act1_R_DIA", true);


        Collider* collider = AddComponent<Collider>();
        collider->SetSize(Vector2(90.0f, 90.0f));
        Vector2 size = collider->GetSize();
        collider->SetCenter(Vector2{ (-0.20f) * size.x, (-0.11f) * size.y });
        mOwner = owner;
    }
    Bullet_Act1_R_DIA::~Bullet_Act1_R_DIA()
    {
    }
    void Bullet_Act1_R_DIA::Initialize()
    {
        Gameobject::Initialize();
    }
    void Bullet_Act1_R_DIA::Update()
    {
        Transform* tr = GetComponent<Transform>();
        Vector2 pos = tr->GetPos();      
        pos.y += 150.0f * static_cast<float>(Time::DeltaTime());
        pos.x -= 150.0f * static_cast<float>(Time::DeltaTime());
        tr->SetPos(pos);

        Gameobject::Update();
    }
    void Bullet_Act1_R_DIA::Render(HDC hdc)
    {
        Gameobject::Render(hdc);
    }
    void Bullet_Act1_R_DIA::Release()
    {
        Gameobject::Release();
    }
}