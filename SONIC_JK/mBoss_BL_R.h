#pragma once
#include "jk_Bullet.h"


namespace jk
{
	class mBoss_BL_R : public Bullet
	{
	public:


		mBoss_BL_R(Gameobject* owner);
		~mBoss_BL_R();

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
