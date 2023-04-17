#pragma once
#include "jk_Gameobject.h"
#include "jk_Sonic.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake : public Gameobject
	{
	public:
		enum class eSnake
		{
			Idle,
			Right_Up,
			Right_Down,
			Left_Up,
			Left_Down,		
			Deth
		};

		Snake(Gameobject* owner);
		~Snake();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eSnake Get_Snake_state() { return mState; }
		virtual Vector2 GetPrevPos() override;
		Vector2 Getmonster() { return mCurpos; }

		void release_animal();

	private:

		void idle();
		void right_up();
		void right_down();
		void left_up();
		void left_down();
		void deth();

		void throw_CompleteEvent();

	private:
		Gameobject* mOwner;
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance_x;
		float mMonmaxdistance_y;
		int mDir_x;
		int mDir_y;
		eSnake mState;
		Vector2 pos;
		float fDist;
		Vector2 prevPos;


		Sonic::eSonicState sonicState;
		int sonicpattern;
	};
}