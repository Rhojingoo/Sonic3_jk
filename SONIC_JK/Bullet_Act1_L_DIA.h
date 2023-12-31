#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class Bullet_Act1_L_DIA : public Bullet
	{
	public:
		Bullet_Act1_L_DIA(Gameobject* owner);
		~Bullet_Act1_L_DIA();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
	};
}
