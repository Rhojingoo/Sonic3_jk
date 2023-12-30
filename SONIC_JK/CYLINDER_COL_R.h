#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class CYLINDER_COL_R : public BackGround
	{
	public:

		CYLINDER_COL_R(Gameobject* owner);
		~CYLINDER_COL_R();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Gameobject* mOwner;
		class Collider* mCollider;	
	};
}
