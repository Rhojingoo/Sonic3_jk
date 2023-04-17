#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Item_Fire : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Death,
		};

		Item_Fire(Gameobject* owner);
		~Item_Fire();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void CreateBlending();
		int GetItemcheck() { return Itemcheck; }



	private:
		void idle();
		void death();

	private:
		Image* mImage;
		Animator* mAnimator;
		Gameobject* mOwner;
		eState itemmState;
		//Sonic::eSonicState sonic_state;
		int mDir;
		Sonic::eSonicState sonicState;
		int Itemcheck;
	};

}
