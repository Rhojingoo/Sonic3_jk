#pragma once
#include "jk_Effect.h"

namespace jk
{
	class Last_Boss_bomb : public Effect
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
		class Image* mImage;
		class Animator* mAnimator;
		eBossState mState;
		Vector2 mPos;
		Gameobject* mOwner;
	};
}
