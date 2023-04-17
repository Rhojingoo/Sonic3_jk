#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"



namespace jk
{
	class Ground;
	class Rigidbody;
	class Monket_Bullet : public Gameobject
	{
	public:
		Monket_Bullet(Gameobject* owner);
		~Monket_Bullet();

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
		Image* mImage;
		Image* mGroundImage;
		Ground* check;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		Vector2 Sonic;
		Gameobject* mOwner;
		Rigidbody* mRigidbody;
	};
}
