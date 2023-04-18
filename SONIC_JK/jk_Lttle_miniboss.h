#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Lttle_miniboss : public Gameobject
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


	private:
		void move();
		void death();


	private:
		Image* mImage;
		Animator* mAnimator;

		float fDist;
		Vector2 pos;
		Vector2 mCenterpos;
		float mMonspeed;
		float mMonmaxdistance;

		int mDir;
		eState mState;
		Gameobject* mOwner;
	};
}