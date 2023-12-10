#pragma once
#include "jk_Gameobject.h"
#include "jk_Bullet.h"
#include "jk_Image.h"
#include "jk_Animator.h"


namespace jk
{
	class Ground;
	class Rigidbody;
	class Canon_Bullet : public Bullet
	{
	public:
		Canon_Bullet(Gameobject* owner);
		~Canon_Bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetGroundImage(Image* image) { mGroundImage = image; }

	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Transform* tr;
		int mDir;
		int check_ground_Cb;
		Gameobject* mOwner;
	};
}
