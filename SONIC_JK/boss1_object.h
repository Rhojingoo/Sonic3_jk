#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Ground;
	class boss1_object;
	class Animator;
	class boss1_object : public Gameobject
	{
	public:
		enum class eBossState
		{
			Idle,
			Up,
			Down,			
		};

		boss1_object();
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
		void SetCheckTargetGround(Ground* ground) { check = ground; }
		int Get_Deathpoint(){ return Death_point; }

	private:
		void idle();
		void up();
		void down();
		void attack_up();
		void attack_down();

	private:
		Image* mImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Vector2 pos;	

		int mDir;
		int attack_check;
		eBossState mState;
		float time;	
		int attack_lotation;
		int Death_point;


		Image* mGroundImage;
		Ground* check;
		int check_map;
		int bullet_check;
	};
}
