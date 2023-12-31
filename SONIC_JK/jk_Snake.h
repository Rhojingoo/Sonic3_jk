#pragma once
#include "jk_Monster.h"

namespace jk
{
	class Animator;
	class Snake : public Monster
	{
	public:
		Snake(Vector2 _Pos);
		Snake(Snake* abc);
		Snake();
		~Snake();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		double TimeSinceStart();

		void SetposSnake(Vector2 set) { pos = set; }

		void SetLife(bool set) { LifeCheck = set; }
		bool GetLife() { return LifeCheck; }

	private:
		Scene* mScene;
		Sound* Death;
		Animator* mAnimator;
		Vector2 pos;
		static bool LifeCheck;
		bool Obdel;


		Snake* snake[6] = {};

		Sonic::eSonicState sonicState;
		Tails::eTailsState tailsState;
	};
}