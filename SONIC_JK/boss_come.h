#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Ground;
	class Rigidbody;
	class Animator;
	class boss_come : public Gameobject
	{
	public:
		enum class eBossState
		{
			Move,
			Jump,
		};

		boss_come(Gameobject* owner);
		~boss_come();

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
		void move();
		void jump();

	private:
		Image* mImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 mCenterpos;
		Vector2 pos;
		float mMonspeed;
		float mMonmaxdistance;

		Image* mGroundImage;
		Ground* check;

		int mDir;
		float fDist;
		eBossState mState;
		float time;
		int check_map;
	};
}
