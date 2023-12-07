#include "Item.h"

namespace jk
{
	Item::Item()
	{
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		Gameobject::Initialize();
	}
	void Item::Update()
	{
		Gameobject::Update();
	}
	void Item::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Item::Release()
	{
		Gameobject::Release();
	}
	void Item::OnCollisionEnter(Collider* other)
	{
	}
	void Item::OnCollisionStay(Collider* other)
	{
	}
	void Item::OnCollisionExit(Collider* other)
	{
	}
}