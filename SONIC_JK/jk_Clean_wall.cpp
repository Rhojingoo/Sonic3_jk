#include "jk_Clean_wall.h"
#include "jk_Item.h"
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
#include "jk_Rock_Pice.h"
#include "Rigidbody.h"
#include "jk_Ground.h"

namespace jk
{
	Clean_wall::Clean_wall()
		: mImage(nullptr)
	
	{
	}
	Clean_wall::~Clean_wall()
	{
	}
	void Clean_wall::Initialize()
	{
	

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(170.0f, 270.0f));	
		
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2{ 661.f, 3033.f });

		Gameobject::Initialize();
	}
	void Clean_wall::Update()
	{
		Gameobject::Update();
	}
	void Clean_wall::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Clean_wall::Release()
	{
		Gameobject::Release();
	}
	void Clean_wall::OnCollisionEnter(Collider* other)
	{
		if (Sonic* mSonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			check->Set_Circlecheck(1);
		}
	}
	void Clean_wall::OnCollisionStay(Collider* other)
	{
	}
	void Clean_wall::OnCollisionExit(Collider* other)
	{
	}
	void Clean_wall::idle()
	{
	}
	void Clean_wall::death()
	{
	}
}