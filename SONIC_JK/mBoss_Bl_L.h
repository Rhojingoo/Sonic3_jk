#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class mBoss_Bl_L : public Bullet
	{
	public:


		mBoss_Bl_L(Gameobject* owner);
		~mBoss_Bl_L();

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
