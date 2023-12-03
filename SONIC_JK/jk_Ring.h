#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Ring : public Gameobject
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
		int GetItemcheck() { return Ringcheck; }



	private:
		void idle();
		void eat();
		void death();

	private:
		Image* mImage;
		Animator* mAnimator;
		Gameobject* mOwner;
		eState Ring_State;
		int Ringcheck;
	};
}
