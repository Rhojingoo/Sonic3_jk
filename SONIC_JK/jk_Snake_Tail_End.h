#pragma once
#include "jk_Gameobject.h"
#include "jk_Monster.h"
#include "jk_Snake_mTaIl.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake_Tail_End : public Monster
	{
	public:
		enum class eSnake
		{
			Right,
			Left,
			Deth
		};

		Snake_Tail_End();
		~Snake_Tail_End();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Set_Snake_body_third(Gameobject* s_body) { snake_body = s_body; }
		virtual Vector2 GetPrevPos() override;

	private:

		void right();
		void left();
		void deth();

	private:
		Image* mImage;
		Animator* mAnimator;
		eSnake mState;
		Snake_mTaIl::eSnake Tail_state;
		Gameobject* snake_body;
		Vector2 prevPos;
	};
}