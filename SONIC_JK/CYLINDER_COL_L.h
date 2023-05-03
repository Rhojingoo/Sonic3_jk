#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class CYLINDER_COL_L : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
		};

		CYLINDER_COL_L(Gameobject* owner);
		~CYLINDER_COL_L ();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();


	private:
		Image* mImage;
		Gameobject* mOwner;
		eState mState;
		Sonic* sonic;

		class Collider* mCollider;
		int mDir;
		Sonic::eSonicState sonicState;
	};
}