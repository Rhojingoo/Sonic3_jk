#pragma once
#include "jk_Effect.h"


namespace jk
{
	class mB_Ldeath : public Effect
	{
	public:
		mB_Ldeath(Gameobject* owner);
		~mB_Ldeath();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void death();

	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
	};
}
