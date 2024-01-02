#pragma once
#include "jk_Snake.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"


namespace jk
{
	class Sound;
	class Image;
	class Animator;
	class Snake_Head : public Snake
	{
	public:
		enum class eSnake
		{
			Idle,
			Right,
			Left,
			Deth
		};

		Snake_Head(Vector2 _Pos);
		Snake_Head();
		~Snake_Head();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eSnake Get_Snake_state() { return mState; }


		Vector2 Gepos() { return mCurpos; }


		Vector2 Getmonster() { return mCurpos; }
		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }
		void release_animal();


	private:
		void idle();
		void right();
		void left();
		void deth();

	private:
		eSnake mState;
		Transform* tr;
		Sound* Death;
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;

	private:
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonmaxdistance_x;
		float mMonmaxdistance_y;
		int mDir_x;
		int mDir_y;


	private:
		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;
	};
}