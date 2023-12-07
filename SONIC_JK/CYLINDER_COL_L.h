#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class CYLINDER_COL_L : public BackGround
	{
	public:

		CYLINDER_COL_L(Gameobject* owner);
		~CYLINDER_COL_L ();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();


	private:
		Gameobject* mOwner;
		class Collider* mCollider;
	};
}
