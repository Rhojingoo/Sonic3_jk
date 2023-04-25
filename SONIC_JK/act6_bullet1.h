#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"



namespace jk
{
	class Ground;
	class Rigidbody;
	class act6_bullet1 : public Gameobject
	{
		enum class eBossState
		{
			Idle,
			Up,
			Down,
		};

	public:
		act6_bullet1();
		~act6_bullet1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Ground* ground) { check = ground; }


		void idle();
		void up();
		void down();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		Image* mImage;
		Animator* mAnimator;
		eBossState mState;
		Image* mGroundImage;
		Rigidbody* mRigidbody;
		Ground* check;
		int check_map;
		Vector2 pos;

		int mDir;
		Vector2 Sonic;	
	};
}
