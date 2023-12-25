#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Boss.h"
#include "boss_come.h"
#include "First_Boss.h"
#include "act6_bullet1.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"


namespace jk
{
	class Pixel_Ground;
	class First_Boss;
	class Animator;
	class boss1_object : public BackGround
	{
	public:
		enum class eBossState
		{
			Idle,
			Up,
			Down,
		};

		boss1_object(Gameobject* onwer);
		~boss1_object();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Set_Deathpoint(int point) { Death_point = point; }
		void SetGroundImage(Image* image) { mGroundImage = image; }
		int Get_Deathpoint() { return Death_point; }

	private:
		void idle();
		void up();
		void down();
		void attack_up();
		void attack_down();

	private:
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* mCollider;
		Sound* Bullet1;

	private:
		First_Boss* boss;
		act6_bullet1* bullet;
		eBossState mState;
		Vector2 pos;
		int mDir;
		float time;
		int attack_check;
		int attack_lotation;
		int Death_point;
		int bullet_check;
	};
}
