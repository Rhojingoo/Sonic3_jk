#pragma once
#include "jk_Gameobject.h"
#include "jk_Effect.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class midlle_boss_shoot : public Effect
	{
	public:
		enum class eState
		{
			Move,
			Attack,
			Death
		};

		midlle_boss_shoot();
		~midlle_boss_shoot();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		void move();
		void attack();
		void death();



	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;

	private:
		float fDist;
		Vector2 pos;
		Vector2 mCenterpos;
		float mMonspeed;
		float mMonmaxdistance;
	};
}
