#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_Animator.h"

namespace jk
{
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
		
		void Set_FinalArea(Vector2 area) { Final_jeepline = area; }
		void Set_StartArea(Vector2 area) { Start_jeepline = area; }


	private:
		void idle();
		void move();


	private:
		eState mState;
		Image* mImage;
		Animator* mAnimator;

		float jeepline_Speed;
		Vector2 Start_jeepline;
		Vector2 Final_jeepline;		
	};

}