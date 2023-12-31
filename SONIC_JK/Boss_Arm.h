#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Image;
	class Rigidbody;
	class Animator;
	class Boss_Arm : public Gameobject
	{
	public:

		Boss_Arm(Gameobject* owner);
		~Boss_Arm();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Set_mDir(int dir) { mDir = dir; }
		void Set_Hurt(int hurt) { mDamege_check= hurt; }
		int Get_grap() { return mGrap; }
		void Set_Grap(int set) { mGrap = set; }

		void Hurt();
	

	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Rigidbody* mSonic_RG;
		Transform* mSonic_Tr;
		Gameobject* mOwner;

	private:
		Vector2 mPos;
		Vector2 mBoss_pos;
		int mDir;
		int mGrap;
		int mMoving_lotation;
		int mDamege_check;
	};
}