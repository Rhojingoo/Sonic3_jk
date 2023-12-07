#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"
#include "jk_Sound.h"

namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class Rock_big : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Up,
			Death,
		};

		Rock_big();
		~Rock_big();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Ground* ground) { check = ground; }

	private:
		void idle();
		void up();
		void death();


	private:
		Sound* Crash;
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		
	private:
		eState mState;
		Ground* check;
		Sonic::eSonicState sonicState;	

	private:
		float timer_RB; 
		float Rb_DisappearTime; 
		float bounceForce_Rb;
		int check_ground_BR;
	};
}
