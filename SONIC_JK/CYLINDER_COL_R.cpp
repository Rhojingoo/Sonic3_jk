#include "CYLINDER_COL_R.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_SONIC.h"
#include "Rigidbody.h"

jk::CYLINDER_COL_R::CYLINDER_COL_R(Gameobject* owner)
	:mOwner(owner)
{
	mOwner = owner;
	sonic = dynamic_cast<Sonic*>(owner);
}

jk::CYLINDER_COL_R::~CYLINDER_COL_R()
{
}

void jk::CYLINDER_COL_R::Initialize()
{
	mCollider = AddComponent<Collider>();
	mCollider->SetSize(Vector2(30.0f, 780.f));
	Transform* tr = GetComponent<Transform>();


	Gameobject::Initialize();
}

void jk::CYLINDER_COL_R::Update()
{
	Gameobject::Update();
}

void jk::CYLINDER_COL_R::Render(HDC hdc)
{
	Gameobject::Render(hdc);
}

void jk::CYLINDER_COL_R::Release()
{
	Gameobject::Release();
}

void jk::CYLINDER_COL_R::OnCollisionEnter(Collider* other)
{

}

void jk::CYLINDER_COL_R::OnCollisionStay(Collider* other)
{
	if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
	{
		sonic->Getsonicstate();
		Vector2 Sonic_Velocity(0.f, 0.f);
		

		Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
		Sonic_Velocity = mSonic_rb->GetVelocity();
		Sonic_Velocity.x = 10000.f;
		mSonic_rb->AddForce(Vector2{ -Sonic_Velocity.x,Sonic_Velocity.y});
	}
}

void jk::CYLINDER_COL_R::OnCollisionExit(Collider* other)
{
}

void jk::CYLINDER_COL_R::idle()
{
}
