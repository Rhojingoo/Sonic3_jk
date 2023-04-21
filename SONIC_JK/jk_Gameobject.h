#pragma once
#include "jk_Entity.h"
#include "jk_Component.h"


namespace jk
{
	class Gameobject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Death,
		};


		Gameobject();
		virtual ~Gameobject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		Gameobject Getowner() { return *mOwner; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
		virtual Vector2 GetPrevPos();


		template <typename T> 
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);
			/*if (compType == jk_ComponentType)
			{
				comp->SetPos()
			}*/

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				T* pComponent = dynamic_cast<T*>(comp);
				if (nullptr != pComponent)
					return pComponent;
			}
			return nullptr;
		}

 		eState GetState() { return mState;}
		void SetState(eState state) { mState = state; }

	private:
		std::vector<Component*> mComponents;
		eState mState;
		Gameobject* mOwner;
	};
}
