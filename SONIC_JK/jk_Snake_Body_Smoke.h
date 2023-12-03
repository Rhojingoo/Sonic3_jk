#pragma once
#include "jk_Gameobject.h"
#include "jk_Snake.h"
#include "jk_Image.h"
#include "jk_Time.h"

namespace jk
{
	class Animator;
	class Snake_Body_Smoke : public Gameobject
	{
	public:
		enum class eSnake
		{		
			Right,			
			Left,	
			Deth
		};

		Snake_Body_Smoke();
		~Snake_Body_Smoke();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
			
		eSnake Get_Snake_state() { return mState; }
		void Set_Snake_Body(Gameobject* s_head) { Head_ch = s_head; }
		virtual Vector2 GetPrevPos() override;

	private:
			
		void right();
		void left();
		void deth();
	
		

	private:		
		Gameobject* Head_ch;
		Animator* mAnimator;
		Image* mImage;
		eSnake mState;
		Vector2 prevPos;
		Snake::eSnake Snake_State;
	};
}