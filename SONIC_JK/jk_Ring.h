#pragma once
#include "Item.h"

namespace jk
{
	class Ring : public Item
	{
	public:
		enum class eState
		{
			Idle,
			Eat,
			Death,
		};

		Ring(Gameobject* owner);
		~Ring();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void CreateBlending();
		int GetItemcheck() { return mRingcheck; }

	private:
		void idle();
		void eat();
		void death();

	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
		eState Ring_State;
		int mRingcheck;
	};
}
