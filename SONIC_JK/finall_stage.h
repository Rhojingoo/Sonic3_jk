#pragma once
#include "jk_BackGround.h"

namespace jk
{
	class finall_stage : public BackGround
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


		void Set_move_stage(int check) {mCheck_Map = check;}
		void Set_end_Stage(int point) { mEnd = point; }
		int Get_end_Stage() {return mEnd;};


	private:
		void idle();
		void move();
		void death();
		void Ending();


	private:
		class Image* mImage;
		class Animator* mAnimator;
		class Rigidbody* mRigidbody;
		class Sound* mRocket_Start;
		eBossState mState;
	
	private:
		Vector2 mPos;
		float mSpeed;
		int mCheck_Map;
		int mEnd;
	};
}
