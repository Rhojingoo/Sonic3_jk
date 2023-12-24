#pragma once
#include "jk_Snake.h"
#include "jk_Snake_Last_Body.h"

#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake_Tail : public Snake
	{
	public:
		enum class eSnake
		{
			Right,
			Left,
			Deth
		};

		Snake_Tail(Snake_Last_Body* set);
		Snake_Tail();
		~Snake_Tail();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void right();
		void left();
	

	private:
		Snake_Last_Body* Body_end;
		std::deque<Vector2> prevPositions;
		Vector2 CurPos;
		Transform* tr;


		Image* mImage;
		Animator* mAnimator;
		eSnake mState;
		Snake_Tail::eSnake Tail_state;
		Snake_Last_Body::eSnake Body_State;


	
	};
}