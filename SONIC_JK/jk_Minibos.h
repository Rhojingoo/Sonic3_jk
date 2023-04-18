#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Minibos : public Gameobject
	{
	public:
		enum class eBossState
		{
			Move,
			Attack,
			Hit,
			Death
		};


		Minibos(Gameobject* owner);
		~Minibos();

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
		void hit();
		void death();


	private:
		Image* mImage;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		eBossState mState;
		Gameobject* mOwner;
	};
}
