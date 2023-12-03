#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"



namespace jk
{
	class Rigidbody;
	class Second_boss_bullet : public Gameobject
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
		Image* mImage;
		Animator* mAnimator;			
		int mDir;
		float mSpeed;
	
	};
}
