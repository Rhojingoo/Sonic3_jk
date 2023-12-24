#pragma once
#include "jk_Snake.h"
#include "jk_Snake_Third_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake_Last_Body : public Snake
	{
	public:
		enum class eSnake
		{
			Right,
			Left,
			Deth
		};
		Snake_Last_Body(Snake_Third_Body* set);
		Snake_Last_Body();
		~Snake_Last_Body();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		

		void right();
		void left();

		eSnake Get_Snake_state() { return mState; }
		Vector2 GetNextPosition();
		Vector2 GetteurnPOs() { return CurPos; }



	private:
		Snake_Third_Body* Body_3;
		std::deque<Vector2> prevPositions;
		Vector2 CurPos;
		Transform* tr;


		Image* mImage;
		Animator* mAnimator;
		eSnake mState;		
		Snake_Last_Body::eSnake snake_body_state;
		Snake_Third_Body::eSnake Body3_State;

	};
}