#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Pixel_Ground;
	class Rigidbody;
	class Animator;
	class Rock_small : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Up,
			Death,
		};

		Rock_small();
		~Rock_small();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { check = ground; }

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

		eState mState;
		Pixel_Ground* check;
		Sonic::eSonicState sonicState;
	
	private:
		float timer_RS ;
		float RS_DisappearTime;
		float bounceForce_RS;
		int check_ground_SR;
	};

}
