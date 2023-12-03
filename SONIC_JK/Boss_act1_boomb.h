#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Boss_act1_boomb : public Gameobject
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
		Image* mImage;
		Animator* mAnimator;
		Gameobject* mOwner;
		int Death_point;
	};
}
