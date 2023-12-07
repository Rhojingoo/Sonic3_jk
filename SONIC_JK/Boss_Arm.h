#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Rigidbody;
	class Animator;
	class Boss_Arm : public Boss
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
		void Set_Hurt(int hurt) { Damege_check= hurt; }
		int Get_grap() { return grap; }

		void Hurt();
	

	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Gameobject* mOwner;

	private:
		Vector2 pos;
		Vector2 Boss_pos;
		int mDir;
		int grap;
		int moving_lotation;
		int Damege_check;
	};
}