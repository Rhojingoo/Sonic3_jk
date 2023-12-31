#pragma once
#include "Item.h"

namespace jk
{
	class Item_Fire : public Item
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
		int GetItemcheck() { return mItemcheck; }



	private:
		void idle();
		void death();

	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
		eState itemmState;
		Sonic::eSonicState sonicState;
		int mItemcheck;
	};

}
