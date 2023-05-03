#pragma once
#include "jk_Entity.h"
#include "jk_Layer.h"

namespace jk
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Destory();
		virtual void Release();


		virtual void OnEnter();
		virtual void OnExit();

		void AddGameobeject(Gameobject* obj, jk_LayerType layer);
		std::vector<Gameobject*>& GetGameobjects(jk_LayerType layer);		



		
	private:
		std::vector<Layer> mLayers;
	};
}