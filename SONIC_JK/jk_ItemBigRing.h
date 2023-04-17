#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class ItemBigRing : public Gameobject
	{
	public:
		enum class eState
		{
			Idle,
			Move,	
		};

		ItemBigRing();
		~ItemBigRing();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void CreateBlending();

	private:
		void idle();
		void move();

	private:
		Image* mImage;
		Animator* mAnimator;
		eState mState;
		int mDir;

	};

}
