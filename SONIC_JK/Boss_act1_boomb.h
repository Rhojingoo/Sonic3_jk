#pragma once
#include "jk_Effect.h"


namespace jk
{
	class Boss_act1_boomb : public Effect
	{
	public:
		enum class eBossState
		{
			Move,
		};

		Boss_act1_boomb(Gameobject* owner);
		~Boss_act1_boomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void Set_Death_point(int point) { Death_point = point; }

	private:
		void move();

	private:
		class Image* mImage;
		class Animator* mAnimator;
		Gameobject* mOwner;
		int Death_point;
	};
}
