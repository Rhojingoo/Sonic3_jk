#pragma once
#include "jk_Monster.h"

namespace jk
{
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

		void SetposSnake(Vector2 set) { mPos = set; }

		void SetLife(bool set) { mLifeCheck = set; }
		bool GetLife() { return mLifeCheck; }

	private:
		Scene* mScene;
		class Sound* mDeath;
		class Animator* mAnimator;
		Snake* mSnake[6] = {};
		Vector2 mPos;
		static bool mLifeCheck;
		bool mObdel;
	};
}