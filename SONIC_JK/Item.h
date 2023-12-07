#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Item	: public Gameobject
	{
	public:
		Item();
		~Item();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}
