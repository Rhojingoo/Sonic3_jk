#pragma once
#include "jk_Snake.h"

namespace jk
{
	class Snake_Head;
	class Image;
	class Animator;
	class Snake_Second_Body : public Snake
	{
	public:
		enum class eSnake
		{
			Right,			
			Left,					
		};
		Snake_Second_Body(Snake_Head* ob);
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
		Vector2 Gepos() { return mCurPos; }
		Vector2 GetteurnPOs() { return mCurPos; }

	private:	
		Snake_Head* mBody_1;
		Vector2 mCurPos;
		Transform* tr;

		Image* mImage;
		Animator* mAnimator;		
		eSnake mState;
		Snake_Second_Body::eSnake Snake_State;
		Snake_Head::eSnake Body1_State;
		
	};
}