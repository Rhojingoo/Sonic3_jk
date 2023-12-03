#include "jk_Clean_wall.h"

#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Collider.h"

namespace jk
{
	Clean_wall::Clean_wall()
		: mCollider(nullptr)
	
	{
	}
	Clean_wall::~Clean_wall()
	{
	}
	void Clean_wall::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(48.0f, 315.0f));			

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