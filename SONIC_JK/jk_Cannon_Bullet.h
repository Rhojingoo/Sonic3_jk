#pragma once
#include "jk_Bullet.h"

namespace jk
{
	class Cannon_Bullet : public Bullet
	{
	public:
		Cannon_Bullet(Gameobject* owner);
		~Cannon_Bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetGroundImage(class Image* image) { mGroundImage = image; }

	private:
		class Image* mImage;
		class Image* mGroundImage;
		class Animator* mAnimator;
		class Rigidbody* mRigidbody;
		class Transform* mTr;
		int mDir;
		int mCheck_Ground;
		Gameobject* mOwner;
	};
}
