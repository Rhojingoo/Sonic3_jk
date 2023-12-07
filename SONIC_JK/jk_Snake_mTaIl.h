#pragma once
#include "jk_Gameobject.h"
#include "jk_Monster.h"
#include "jk_Snake_body2.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake_mTaIl : public Monster
	{
	public:
		enum class eSnake
		{
			Right,
			Left,
			Deth
		};

		Snake_mTaIl();
		~Snake_mTaIl();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		
		eSnake Get_Snake_state() { return mState; }
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
		Gameobject* snake_body;
		Snake_body2::eSnake bodyend_state;
		Vector2 prevPos;
	};
}