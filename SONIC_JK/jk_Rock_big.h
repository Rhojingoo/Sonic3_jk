#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Pixel_Ground;
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
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixelGround_check = ground; }

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

	private:
		eState mState;
		Pixel_Ground* mPixelGround_check;
		Sonic::eSonicState sonicState;

	private:
		float mTime;
		float mDisappearTime;
		int mCheckGR;
	};
}
