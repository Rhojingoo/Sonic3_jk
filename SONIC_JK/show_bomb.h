#pragma once
#include "jk_Boss.h"

namespace jk
{
	class show_bomb : public Boss
	{
	public:
		enum class eState
		{
			Move,
			Death
		};

		show_bomb(Gameobject* owner);
		~show_bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCheckTargetGround(class Pixel_Ground* ground) { mPixelGround = ground; }

	private:
		void move();
		void death();
		void bomb();


	private:
		class Sound* Bomber_shot;
		class Pixel_Ground* mPixelGround;
		class Image* mImage;
		class Image* mGroundImage;
		class Animator* mAnimator;
		eState mState;
		Gameobject* mOwner;

		Vector2 mPos;
		Vector2 mPlayer_pos;
		float mMonspeed;
		int mCheck_Ground;
	};
}