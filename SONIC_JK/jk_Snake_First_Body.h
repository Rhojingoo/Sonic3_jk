#pragma once
#include "jk_Snake.h"
#include "jk_Snake_Head.h"

namespace jk
{
	
	class Image;
	class Animator;
	class Snake_First_Body : public Snake 
	{
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
		void SetHeadOB(Snake_Head* set) { mHead_ch = set; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
			
		eSnake Get_Snake_state() { return mState; }
		Vector2 GetteurnPOs() {	return mCurPos;}

	private:			
		void right();
		void left();


	private:		
		Snake_Head* mHead_ch;
		Transform* tr;
		Animator* mAnimator;
		Image* mImage;
		eSnake mState;

		Vector2 mCurPos;
		Vector2 mPrevPos;
		Snake_First_Body::eSnake Snake_State;
		Snake_Head::eSnake Head_state;
	};
}