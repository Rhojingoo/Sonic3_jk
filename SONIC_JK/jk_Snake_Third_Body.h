#pragma once
#include "jk_Snake.h"
#include "jk_Snake_Second_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{	
	class Animator;
	class Snake_Third_Body : public Snake
	{
	public:
		enum class eSnake
		{
			Right,
			Left,
			Deth
		};
		Snake_Third_Body(Snake_Second_Body* ob);
		Snake_Third_Body();
		~Snake_Third_Body();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		eSnake Get_Snake_state() { return mState; }
		Vector2 GetNextPosition();
		Vector2 GetteurnPOs() { return CurPos; }

	private:
			
		void right();
		void left();
		void deth();

	private:
		Snake_Second_Body* Body_2;
		std::deque<Vector2> prevPositions;
		Vector2 CurPos;
		Transform* tr;


		Image* mImage;
		Animator* mAnimator;

		eSnake mState;
		Snake_Third_Body::eSnake snake_body_state;
		Snake_Second_Body::eSnake Body2_State;
	};
}