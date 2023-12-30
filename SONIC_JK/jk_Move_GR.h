#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Rigidbody;
	class Animator;
	class Move_GR : public BackGround
	{
	public:
		enum class eState
		{
			Up,
			Down,
		};

		Move_GR();
		~Move_GR();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }
		void Setmaxdistance(float max) { mMonmaxdistance = max; }

	private:
		void up();
		void down();


	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;

		Vector2 mCenterpos;
		Vector2 mPos;
		float mMonspeed;
		float mMonmaxdistance;
		float mFinalDistance;
		int mDir;


	};

}