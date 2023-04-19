#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	class Animator;
	class mBoss_BL_R : public Gameobject
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
		Image* mImage;
		Animator* mAnimator;
	};
}
