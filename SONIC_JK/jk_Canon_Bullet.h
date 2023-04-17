#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Animator.h"


namespace jk
{
	class Ground;
	class Rigidbody;
	class Canon_Bullet : public Gameobject
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
		Ground* check;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		Vector2 Sonic;
		Gameobject* mOwner;
	};
}
