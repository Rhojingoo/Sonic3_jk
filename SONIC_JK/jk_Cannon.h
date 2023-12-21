#pragma once
#include "jk_Gameobject.h"
#include "jk_Monster.h"
#include "jk_Image.h"
#include "jk_Sonic.h"
#include "jk_Tails.h"
#include "jk_Time.h"
#include "jk_Canon_Bullet.h"


namespace jk
{
	class Pixel_Ground;
	class Rigidbody;
	class Animator;
	class Cannon : public Monster
	{
	public:
		enum class eCannon
		{
			Idle,
			Right,
			Left,			
			Death
		};

		Cannon(Gameobject* owner);
		~Cannon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetGroundImage(Image* image) { mGroundImage = image; }
		void SetCheckTargetGround(Pixel_Ground* ground) { check = ground; }


		Vector2 Getmonster() { return pos; }
		int GetDir() {	return mDir	;}


	private:
		
		void idle();
		void right();
		void left();
		void death();

		void throw_CompleteEvent();
		void release_animal();
		void Ground_check();

	private:
		Sound* Death;
		Gameobject* mOwner;
		Image* mImage;
		Image* mImage1;
		Image* mGroundImage;
		Image* mGroundImage2;
		Animator* mAnimator;
		Pixel_Ground* check;
		Rigidbody* mRigidbody;
		Image* bullet_groundImage;

	private:
		eCannon mState;
		Vector2 pos;
		int mDir;
		int check_map;
		bool _death;

	private:
		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;
		Canon_Bullet* bullet; 
		Transform* bullet_tr;
		Rigidbody* bullet_rb;

	}; 
}