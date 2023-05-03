#include "jk_MGEmerald.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Input.h"

#include "jk_EmeraldSonic.h"

jk::MGEmerald::MGEmerald()
	: mState(eState::Idle)
{
	Transform* tr = GetComponent<Transform>();
	tr->SetPos(Vector2(595.0f, -200.0f));


}

jk::MGEmerald::~MGEmerald()
{
}

void jk::MGEmerald::Initialize()
{
	Transform* tr = GetComponent<Transform>();
	//tr->SetPos(Vector2(595.0f, -200.0f));
	mImage = Resources::Load<Image>(L"Emerald", L"..\\Resources\\Mini_BG2.bmp");
	mAnimator = AddComponent<Animator>();
	mAnimator->CreateAnimation(L"Emerald", mImage, Vector2(24, 2653), Vector2(32, 32), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1f);

	mAnimator->Play(L"Emerald", true);

	Collider* collider = AddComponent<Collider>();
	
	Vector2 size = collider->GetSize();
	Vector2 center = Vector2{ (-0.15f) * size.x, (-0.35f) * size.y };
	collider->SetCenter(center);
	collider->SetPos(tr->GetPos() + center);

	Gameobject::Initialize();
}

void jk::MGEmerald::Update()
{
	if (isLoad == true)
	{
		SceneManager::LoadScene(jk_SceneType::GamePlay);
	}
	if (Input::GetKeyDown(eKeyCode::UP)) b = true;
	if(b)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.y += 160.f * static_cast<float>(Time::DeltaTime());
		tr->SetPos(pos);
		Gameobject::Update();
	}

}

void jk::MGEmerald::Render(HDC hdc)
{
	Gameobject::Render(hdc);
}

void jk::MGEmerald::Release()
{
	Gameobject::Release();
}

void jk::MGEmerald::OnCollisionEnter(Collider* other)
{

	if (EmeraldSonic* sonic = dynamic_cast<EmeraldSonic*>(other->GetOwner()))
	{
		if (isLoad == false)
		{
			isLoad = true;
			/*SceneManager::LoadScene(jk_SceneType::GamePlay);*/
		}
	}
	
}

void jk::MGEmerald::OnCollisionStay(Collider* other)
{
}

void jk::MGEmerald::OnCollisionExit(Collider* other)
{
}

void jk::MGEmerald::idle()
{
	mAnimator->Play(L"Emerald", true);

}
