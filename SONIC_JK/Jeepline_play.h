#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Jeepline_play : public Gameobject
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

	private:
		void idle();
		void move();


	private:
		Gameobject* mOwner;
		eState mState;
		Image* mImage;
		Animator* mAnimator;

		int mDir;
		float jeepline_Speed;
		Vector2 pos;	
		Vector2 Start_jeepline;
		Vector2 Final_jeepline;

		Sonic::eSonicState sonicState;
		int sonicpattern;
		
	};

}