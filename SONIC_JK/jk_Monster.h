#pragma once
#include "jk_Gameobject.h"
#include "jk_Transform.h"

namespace jk 
{
	class Monster : public Gameobject
	{
	public:
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Setpos_monster(Vector2 set) { _pos = set; }
		Vector2 Getpos_monster() { return _pos; }

	private:
		Transform* tr = nullptr;
		Vector2 _pos = {};
	};
}



