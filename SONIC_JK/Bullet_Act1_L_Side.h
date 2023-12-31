#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class Bullet_Act1_L_Side : public Bullet
	{
	public:
		Bullet_Act1_L_Side(Gameobject* owner);
		~Bullet_Act1_L_Side();

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
