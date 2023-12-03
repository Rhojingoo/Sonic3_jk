#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Last_Boss_bomb : public Gameobject
	{
	public:
		enum class eBossState
		{
			Move,
			Death,
		};

		Last_Boss_bomb(Gameobject* owner);
		~Last_Boss_bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void move();
		void death();
		void complete_bomb();

	private:
		Image* mImage;
		Animator* mAnimator;
		eBossState mState;
		Vector2 pos;
		Gameobject* mOwner;
	};
}
