#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_Sound.h"
#include "jk_Time.h"

namespace jk
{
	class Ground;
	class Animator;
	class show_bomb : public Gameobject
	{
	public:
		enum class eState
		{
			Move,
			Death
		};

		show_bomb(Gameobject* owner);
		~show_bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCheckTargetGround(Ground* ground) { check = ground; }

	private:
		void move();
		void death();
		void bomb();


	private:
		Sound* Bomber_shot;
		Image* mImage;
		Image* mGroundImage;
		Animator* mAnimator;
		eState mState;
		Ground* check;
		Gameobject* mOwner;

		Vector2 pos;
		Vector2 Player_pos;
		float mMonspeed;
		int check_ground;
	};
}