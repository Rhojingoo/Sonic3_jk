#pragma once
#include "jk_Snake.h"
#include "jk_Snake_Last_Body.h"

namespace jk
{

	class Image;
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
		Snake_Last_Body* mBody_end;
		Vector2 mCurPos;
		Transform* tr;


		Image* mImage;
		Animator* mAnimator;
		eSnake mState;
		Snake_Tail::eSnake Tail_state;
		Snake_Last_Body::eSnake Body_State;	
	};
}