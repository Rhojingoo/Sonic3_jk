#pragma once
#include "jk_BackGround.h"


namespace jk
{
	class Image;
	class Rigidbody;
	class Animator;
	class Jeepline_play : public BackGround
	{
	public:
		enum class eState
		{
			Idle,
			Move,		
		};

		Jeepline_play();
		~Jeepline_play();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		
		void Set_FinalArea(Vector2 area) { mFinal_jeepline = area; }
		void Set_StartArea(Vector2 area) { mStart_jeepline = area; }


	private:
		void idle();
		void move();


	private:
		eState mState;
		Image* mImage;
		Animator* mAnimator;

		float mJeepline_Speed;
		Vector2 mStart_jeepline;
		Vector2 mFinal_jeepline;		
	};

}