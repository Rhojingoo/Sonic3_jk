#include "jk_Gameobject.h"
#include "jk_Transform.h"

namespace jk
{
	Gameobject::Gameobject()
		:mState(eState::Active)
	{
		mComponents.resize((UINT)jk_ComponentType::End);
		AddComponent<Transform>();
	}

	Gameobject::~Gameobject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void Gameobject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}
	}
	
	void Gameobject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}
	}
	
	void Gameobject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Render(hdc);
		}
	}

	void Gameobject::Release()
	{

	}
	void Gameobject::OnCollisionEnter(Collider* other)
	{
	}
	void Gameobject::OnCollisionStay(Collider* other)
	{
	}
	void Gameobject::OnCollisionExit(Collider* other)
	{
	}

	Vector2 Gameobject::GetPrevPos()
	{
		return Vector2::Zero;
	}


}

