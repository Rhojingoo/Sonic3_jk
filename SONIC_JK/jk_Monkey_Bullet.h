#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class Monkey_Bullet : public Bullet
	{
	public:
		Monkey_Bullet(Gameobject* owner);
		~Monkey_Bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		Vector2 Getmonster_pos() { return mCurpos; }

	private:
		class Rigidbody* mRigidbody;
		class Image* mImage;
		class Image* mGroundImage;
		class Animator* mAnimator;
		Transform* mTr;
		Gameobject* mOwner;		
		Vector2 mCurpos;	
		int mCheck_Ground;
	};
}
