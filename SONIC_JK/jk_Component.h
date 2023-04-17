#pragma once
#include "jk_Entity.h"


namespace jk
{	
	class Gameobject;
	class Component : public Entity
	{
	public:
		Component(jk_ComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

 		jk_ComponentType GetType() { return mType; }
		void SetOwner(Gameobject* owner) { mOwner = owner; }
		Gameobject* GetOwner() { return mOwner; }

	private:
		const jk_ComponentType mType;
		Gameobject* mOwner;
	};
}
