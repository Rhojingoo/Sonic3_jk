#pragma once
class Jeep_line_Handle
{
};

#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Jeep_line_Handle : public Gameobject
	{
	public:
		enum class eState
		{		
			Idle,		
		};

		Jeep_line_Handle();
		~Jeep_line_Handle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }
		void SetAngle(float ang) { angle = ang; }
		void SetDirect(int dir) { mDir_x = dir; }
		int Getjeepline_state() { return Jeepline_state; }

		int GetDir() {	return mDir_x;}

	private:	
		void idle();

	

	private:
		Gameobject* mOwner;
		eState mState;
		Image* mImage;
		Animator* mAnimator;
		Vector2 mCenterpos;
		int mDir_x;
		Vector2 pos;

	
		Sonic::eSonicState sonicState;
		float angle;
		int Jeepline_state;
	};

}