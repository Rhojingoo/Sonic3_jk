#pragma once
#include "jk_Gameobject.h"
#include "jk_Monster.h"
#include "jk_Monkey_Bullet.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Sound.h"

namespace jk
{
	class Pixel_Ground;
	class Animator;
	class Monkey : public Monster
	{
	public:
		enum class eMonkey
		{
			L_Move_UP,
			L_Move_DOWN,
			L_Throw,
			R_Throw,	
			Turn,
			Death,		
		};

		Monkey(Gameobject* owner);
		~Monkey();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { check = ground; }
		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }

		Vector2 Getmonster_pos() { return pos; }

	private:
		void Lmove_up();
		void Lmove_down();
		void Lthrows();
		void Rthrows();
		void turn();
		void death();

		void throw_CompleteEvent();
		void release_animal();


	private:
		Gameobject* mOwner;
		Pixel_Ground* check;
		Sound* Death;
		Image* mImage;
		Image* mImage1;
		Image* mGroundImage;
		Animator* mAnimator;	
		Transform* tr;

		eMonkey mState;
		Vector2 mCenterpos;	
		Vector2 pos;
		float mMonspeed;
		float mMonmaxdistance;
		float fDist;
		int mDir;
		int death_point;
		int animal_point;

		Vector2 mSonic;
		int sonicpattern;
		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;

		Monkey_Bullet* bullet;
		Transform* bullet_tr;
		Rigidbody* bullet_rb;
	};
}