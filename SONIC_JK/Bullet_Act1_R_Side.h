#pragma once
#include "jk_Gameobject.h"
#include "jk_Bullet.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"



namespace jk
{
	class Bullet_Act1_R_Side : public Bullet
	{
	public:
		Bullet_Act1_R_Side(Gameobject* owner);
		~Bullet_Act1_R_Side();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		Animator* mAnimator;
		Gameobject* mOwner;
	};
}
