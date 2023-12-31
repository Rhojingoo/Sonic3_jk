#pragma once
#include "jk_Bullet.h"


namespace jk
{
	class Image;
	class Pixel_Ground;
	class Rigidbody;
	class act6_bullet1 : public Bullet
	{
	public:
		act6_bullet1();
		~act6_bullet1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { mPixel_Ground = ground; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Pixel_Ground* mPixel_Ground;
		Vector2 mPos;
	};
}
