#pragma once
#include "jk_Snake.h"
#include "jk_Snake_First_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake_Second_Body : public Snake
	{
		Snake_First_Body* _Head;
	public:
		enum class eSnake
		{
			Right,			
			Left,					
		};
		Snake_Second_Body(Snake_First_Body* ob);
		Snake_Second_Body();
		~Snake_Second_Body();

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
		Snake_First_Body* Body_1;
		std::deque<Vector2> prevPositions;
		Vector2 CurPos;
		Transform* tr;

		Image* mImage;
		Animator* mAnimator;		
		eSnake mState;
		Snake_Second_Body::eSnake Snake_State;
		Snake_First_Body::eSnake Body1_State;
		
	};
}