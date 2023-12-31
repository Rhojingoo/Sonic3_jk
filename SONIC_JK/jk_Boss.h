#pragma once
#include "jk_Gameobject.h"
namespace jk
{
	class Boss : public Gameobject
	{
	public:
		Boss();
		~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	};
}


