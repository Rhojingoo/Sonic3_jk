#pragma once
#include "jk_Boss.h"
#include "jk_SONIC.h"

namespace jk
{	
	class Sound;
	class Image;
	class Sonic;
	class Rigidbody;
	class Animator;
	class Minibos : public Boss
	{
	public:
		enum class eState
		{
			Down,
			Up,
			Left,
			Right,
			Waiting,
			Atack,
			Hurt,
			Death
		};


		Minibos(Gameobject* owner);
		~Minibos();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void down();
		void up();
		void right();
		void left();
		void waiting();
		void atack();
		void hurt();
		void death();

	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;
		Rigidbody* mRigidbody;
		Sound* mMiniboss2;
		Sound* mBoss_hit;
		Sound* mMinboss_death;
		Sound* mAct2_music;


		Gameobject* mOwner;
		Vector2 mCenterpos;
		Vector2 mPos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;		
		float fDist;
		float mTime_Check;
		int mAttack;		
		float mTime;
		int mAttack_check;
		Sonic::eSonicState sonicState;

		int mDeath; //다음장면으로 가기위한변수
		int mMap_check;

	};
}
