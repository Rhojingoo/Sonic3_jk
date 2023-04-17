#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Jeep_line_Handle;
	class Rigidbody;
	class Animator;
	class Jeep_line : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Jeep_Line9,
			Jeep_Line8,
			Jeep_Line7,
			Jeep_Line6,
			Jeep_Line5,
			Jeep_Line4,
			Jeep_Line3,
			Jeep_Line2,
			Jeep_Line1,

		};

		Jeep_line(Gameobject* owner);
		~Jeep_line();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCheck_JeepLine(Jeep_line_Handle* handle) { JL_Handle = handle; }

	private:
		void idle();
		void Jeep_line9();
		void Jeep_line8();
		void Jeep_line7();
		void Jeep_line6();
		void Jeep_line5();
		void Jeep_line4();
		void Jeep_line3();
		void Jeep_line2();
		void Jeep_line1();

	


	private:
		Gameobject* mOwner;
		eState mState;
		Image* mImage;

		Animator* mAnimator;
		Vector2 mCenterpos;
		Vector2 mCurpos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		Vector2 pos;

		float fDist;
		Vector2 mSonic;
		float rotationDegree;
		Sonic::eSonicState sonicState;
		int sonicpattern;	
		int JL_State;
		Jeep_line_Handle* JL_Handle;
	};

}