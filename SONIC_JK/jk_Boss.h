#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Boss : public Gameobject
	{
	public:
		enum class eBossState
		{
			Move,
			Attack,
			Hit,
			Death
		};


		Boss(Gameobject* owner);
		~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;



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
