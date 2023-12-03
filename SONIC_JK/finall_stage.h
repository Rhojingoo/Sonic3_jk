#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"


namespace jk
{
	class boss1_object;
	class Rigidbody;
	class Animator;
	class finall_stage : public Gameobject
	{
	public:
		enum class eBossState
		{
			Idle,
			Move,
			Death,
		};

		finall_stage();
		~finall_stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Bomb();


		void Set_move_stage(int check) {check_map = check;}
		void Set_end_Stage(int point) { end = point; }
		int Get_end_Stage() {return end;};


	private:
		void idle();
		void move();
		void death();
		void Ending();


	private:
		Image* mImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Sound* Rocket_Start;
		eBossState mState;
	
	private:
		Vector2 pos;
		float mSpeed;
		int check_map;
		int end;
	};
}
