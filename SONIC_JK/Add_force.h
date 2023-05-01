#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Add_force : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Add_force();
		~Add_force();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetAddforce(int a) { up_add = a; }


	private:
		void idle();
		void death();


	private:
		Gameobject* mOwner;
		eState mState;		

		class Collider* mCollider;	
		Sonic::eSonicState sonicState;		
		Rigidbody* mRigidbody;
		
		int up_add;
	};

}
