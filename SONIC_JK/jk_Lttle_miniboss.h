#pragma once
#include "jk_Effect.h"

namespace jk
{
	class Lttle_miniboss : public Effect
	{
	public:
		enum class eState
		{
			Move,
			Death
		};
		Lttle_miniboss();
		~Lttle_miniboss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void move();
		void death();

	private:
		class Image* mImage;
		class  Animator* mAnimator;
		Vector2 mPos;
		Vector2 mCenterpos;
		int mDir;
		float fDist;
		float mMonspeed;
		float mMonmaxdistance;	
		eState mState;		
	};
}