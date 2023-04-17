#pragma once
#include "jk_Entity.h"
#include "jk_Gameobject.h"

namespace jk
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update(); 
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameobject(Gameobject* gameObj);
		std::vector<Gameobject*>& GetGameobjects() { return mGameobjects; }


	private:
		std::vector<Gameobject*> mGameobjects;
	};
}
