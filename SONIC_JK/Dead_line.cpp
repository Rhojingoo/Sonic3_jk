#include "Dead_line.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Time.h"
#include "jk_Camera.h"
#include "jk_Object.h"
#include "jk_Blending.h"
#include "jk_Ground.h"

#include "jk_SONIC.h"


namespace jk
{
	Dead_line::Dead_line()
	{
	}
	Dead_line::~Dead_line()
	{
	}
	void Dead_line::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(3000.0f, 100.0f));	
		Transform* tr = GetComponent<Transform>();	

		Gameobject::Initialize();
	}

	void Dead_line::Update()
	{
		Gameobject::Update();
	}

	void Dead_line::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}

	void Dead_line::Release()
	{
		Gameobject::Release();
	}

	void Dead_line::OnCollisionEnter(Collider* other)
	{
	}
	void Dead_line::OnCollisionStay(Collider* other)
	{
	}
	void Dead_line::OnCollisionExit(Collider* other)
	{
	}

	void Dead_line::idle()
	{
	}
	void Dead_line::death()
	{
	}
}