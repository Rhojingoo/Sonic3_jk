#include "jk_Component.h"



namespace jk
{
	Component::Component(jk_ComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{
	}

	void Component::Update()
	{
	}

	void Component::Render(HDC hdc)
	{
	}

	void Component::Release()
	{
	}
}
