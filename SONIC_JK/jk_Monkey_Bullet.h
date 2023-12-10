#pragma once
#include "jk_Gameobject.h"
#include "jk_Bullet.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"


namespace jk
{
	class Ground;
	class Rigidbody;
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
		Rigidbody* mRigidbody;
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Transform* tr;
		Gameobject* mOwner;		
		Vector2 mCurpos;	
		int check_ground_Mb;
	};
}
