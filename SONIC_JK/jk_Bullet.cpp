#include "jk_Bullet.h"

namespace jk
{
	Bullet::Bullet()
	{
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Initialize()
	{
		Gameobject::Initialize();
	}
	void Bullet::Update()
	{
		Gameobject::Update();
	}
	void Bullet::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Bullet::Release()
	{
		Gameobject::Release();
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
	}
	void Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}