#include "jk_Monster.h"

namespace jk
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		Gameobject::Initialize();
	}
	void Monster::Update()
	{
		Gameobject::Update();
	}
	void Monster::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Monster::Release()
	{
		Gameobject::Release();
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}
}