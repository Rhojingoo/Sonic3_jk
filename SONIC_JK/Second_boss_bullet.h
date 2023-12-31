#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class Second_boss_bullet : public Bullet
	{

		public:
		Second_boss_bullet();
		~Second_boss_bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Set_mDir(int dir) { mDir = dir; }

	private:
		class Image* mImage;
		class Animator* mAnimator;			
		int mDir;
		float mSpeed;
	
	};
}
