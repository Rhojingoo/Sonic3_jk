#include "Deatht_line_act6.h"
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
	Deatht_line_act6::Deatht_line_act6()
	{
	}
	Deatht_line_act6::~Deatht_line_act6()
	{
	}
	void Deatht_line_act6::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(3000.0f, 100.0f));
		Transform* tr = GetComponent<Transform>();

		Gameobject::Initialize();
	}
	void Deatht_line_act6::Update()
	{
		Gameobject::Update();
	}
	void Deatht_line_act6::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Deatht_line_act6::Release()
	{
		Gameobject::Release();
	}
	void Deatht_line_act6::OnCollisionEnter(Collider* other)
	{
	}
	void Deatht_line_act6::OnCollisionStay(Collider* other)
	{
	}
	void Deatht_line_act6::OnCollisionExit(Collider* other)
	{
	}
	void Deatht_line_act6::idle()
	{
	}
	void Deatht_line_act6::death()
	{
	}
}