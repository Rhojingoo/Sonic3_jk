#pragma once
#include "jk_Snake.h"
#include "jk_Snake_Head.h"
#include "jk_Monster.h"
#include "jk_Snake.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include <deque>

namespace jk
{
	class Animator;
	class Snake_First_Body : public Snake 
	{
		Snake_Head* _Head;
	public:
		enum class eSnake
		{		
			Right,			
			Left,	
			Deth
		};

		Snake_First_Body(Snake_Head* _Head);
		Snake_First_Body();
		~Snake_First_Body();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		void SetHeadOB(Snake_Head* set) { Head_ch = set; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
			
		eSnake Get_Snake_state() { return mState; }
		Vector2 GetNextPosition();
		Vector2 GetteurnPOs() {	return CurPos;}

	private:			
		void right();
		void left();

	
		

	private:		
		Snake_Head* Head_ch;
		std::deque<Vector2> prevPositions;
		Transform* tr;
		Animator* mAnimator;
		Image* mImage;
		eSnake mState;

		Vector2 CurPos;
		Vector2 prevPos;
		Snake_First_Body::eSnake Snake_State;
		Snake_Head::eSnake Head_state;

	};
}