#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_Sonic.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"


namespace jk
{	
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
		Sound* Miniboss2;
		Sound* Boss_hit;
		Sound* Minboss_death;
		Sound* Act2_music;


		Gameobject* mOwner;
		Vector2 mCenterpos;
		Vector2 pos;
		float mMonspeed;
		float mMonmaxdistance;
		int mDir;		
		float fDist;
		float time_check;
		int attack;		
		float time;

		int attack_check;
		Sonic::eSonicState sonicState;

		int Death; //다음장면으로 가기위한변수
		int map_check;

	};
}
