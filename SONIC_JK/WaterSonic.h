#pragma once
#include "jk_Gameobject.h"
#include "jk_Sonic.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class WaterSonic : public Gameobject
	{
	public:
		enum class State
		{
			Idle,
			Collision_Ground,
		};


		WaterSonic(Gameobject* owner);
		~WaterSonic();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void idle();
		void collsion_ground();
		void water_effect();

	private:
		Gameobject* mOwner;
		Sonic* sonic;
		Animator* mAnimator;
		Vector2 mSonic;
		State mState;

		int mDir;
		int shield_bounce;
	};

}
