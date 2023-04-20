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
			Idle,
			Move,
			Side_Dianogol,
			Dianogol_Down,
			Down_Dianogol,
			Side_Down,

			Attack_Side,
			Attack_Dianogol,
			Attack_Down,

			Hurt_Down,
			Hurt_Side,
			Hurt_Dianogol,

			Death
		};


		Boss(Gameobject* owner);
		~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;



	private:

		void idle();
		void move();
		void side_down();
		void side_dianogol();
		void dianogol_down();
		void down_dianogol();		

		void attack_side();
		void attack_dianogol();
		void attack_down();

		void hurt_down();
		void hurt_side();
		void hurt_dianogol();

		void death();
	

	private:
		Image* mImage;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		Vector2 pos;

		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		float fDist;
		eBossState mState;
		Gameobject* mOwner;

		int time;
		int starscene;
	};
}
