#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class Bullet_Act1_R_DIA : public Bullet
	{
	public:
		Bullet_Act1_R_DIA(Gameobject* owner);
		~Bullet_Act1_R_DIA();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
	};
}
