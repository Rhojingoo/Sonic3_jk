#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class Image;
	class Pixel_Ground;
	class Rigidbody;
	class Animator;
	class Rock_Pice : public BackGround
	{
	public:
		Rock_Pice();
		~Rock_Pice();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }


	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Pixel_Ground* mPixel_Ground;


	private:
		float mTime = 0.0f; 
		float mBounce_Force = 300.0f;
		int mCheck_Ground = 0;
	};
}
