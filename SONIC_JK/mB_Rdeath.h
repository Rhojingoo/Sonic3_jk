#pragma once
#include "jk_Gameobject.h"
#include "jk_Effect.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class mB_Rdeath : public Effect
	{
	public:
		mB_Rdeath(Gameobject* owner);
		~mB_Rdeath();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void death();

	private:
		Image* mImage;
		Animator* mAnimator;
		Gameobject* mOwner;
	};
}
