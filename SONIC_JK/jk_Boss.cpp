#include "jk_Boss.h"

namespace jk
{
	Boss::Boss()
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
		Gameobject::Initialize();
	}
	void Boss::Update()
	{
		Gameobject::Update();
	}
	void Boss::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Boss::Release()
	{
		Gameobject::Release();
	}
	void Boss::OnCollisionEnter(Collider* other)
	{
	}
	void Boss::OnCollisionStay(Collider* other)
	{
	}
	void Boss::OnCollisionExit(Collider* other)
	{
	}
}