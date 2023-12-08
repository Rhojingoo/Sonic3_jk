#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"


namespace jk
{
	class boss1_object;
	class Rigidbody;
	class Animator;
	class boss1_body : public Boss
	{
	public:
		enum class eBossState
		{
			Idle,
			Move,
			Hurt,
			Death,
			Attack_Up,
			Attack_Down,
		};

		boss1_body();
		~boss1_body();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		int Get_BossDeath() { return  Death_point; }
		void Set__BossDeath(int point) { Death_point = point; }

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Ground* ground) { check = ground; }


	private:
		void idle();
		void move();
		void hurt();
		void death();
		void attack_up();
		void attack_down();

	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* mCollider;

	private:
		Sound* Boss_Hit;
		Sound* Boss_Bomb;
		Sound* Boss_Start;
		Sound* Act6_music;

	private:
		eBossState mState;
		Sonic::eSonicState sonicState;
		boss1_object* boss_ob;
		Ground* check;

	private:
		Vector2 pos;
		float time;
		int Death_point;
		int Damege_check;
		int check_map;
	};
}
