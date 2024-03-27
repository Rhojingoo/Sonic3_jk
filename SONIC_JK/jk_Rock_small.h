#pragma once
#include "jk_BackGround.h"
#include "jk_SONIC.h"

namespace jk
{
	class Image;
	class Sound;
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
		Sound* mCrash;
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;

		eState mState;
		Pixel_Ground* check;
		Sonic::eSonicState sonicState;

	private:
		float mTime;
		float mDisappearTime;
		int mCheckGR;
	};

}
