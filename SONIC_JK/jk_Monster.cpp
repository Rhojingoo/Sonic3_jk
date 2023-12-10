#include "jk_Monster.h"

namespace jk
{
	Monster::Monster()
	{
		tr = GetComponent<Transform>();
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
		_pos = tr->GetPos();

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