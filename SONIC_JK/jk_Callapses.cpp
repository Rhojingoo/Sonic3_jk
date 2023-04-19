#include "jk_Callapses.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
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
	Callapses::Callapses()
	{
		mImage = Resources::Load<Image>(L"Rock_Platform2", L"..\\Resources\\Rock_Platform.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Gr_collapses", mImage, Vector2(499, 634), Vector2(136, 88), Vector2(0, 0), 1, 1, 1, Vector2::Zero, 0.1);
		
		mAnimator->Play(L"Gr_collapses", true);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		//Collider* collider = AddComponent<Collider>();
		//collider->SetSize(Vector2(180.0f, 120.0f));
		//Vector2 size = collider->GetSize();
		//collider->SetCenter(Vector2{ (-0.15f) * size.x, (-0.35f) * size.y });

		Gameobject::Initialize();
	}
	Callapses::~Callapses()
	{
	}
	void Callapses::Initialize()
	{
		Gameobject::Initialize();
	}
	void Callapses::Update()
	{
		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		Gameobject::Update();
	}
	void Callapses::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Callapses::Release()
	{
		Gameobject::Release();
	}
	void Callapses::OnCollisionEnter(Collider* other)
	{
	}
	void Callapses::OnCollisionStay(Collider* other)
	{
	}
	void Callapses::OnCollisionExit(Collider* other)
	{
	}
	void Callapses::idle()
	{
	}
	void Callapses::death()
	{
	}
}
