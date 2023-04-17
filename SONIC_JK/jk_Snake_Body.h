#pragma once
#include "jk_Gameobject.h"
#include "jk_Snake_Body_Smoke.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Snake_Body : public Gameobject
	{
	public:
		enum class eSnake
		{
			Right,			
			Left,			
			Deth
		};

		Snake_Body();
		~Snake_Body();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eSnake Get_Snake_state() { return mState; }
		void Set_Snake_Body(Gameobject* s_head) { Body_smoke = s_head; }
		virtual Vector2 GetPrevPos() override;

	private:


		void right();
		void left();
		void deth();

	private:
		Gameobject* mOwner;
		Image* mImage;
		Animator* mAnimator;		
		Vector2 pos;
		Gameobject* Body_smoke;
		Vector2 prevPos;		
		eSnake mState;

		Snake_Body_Smoke::eSnake Snake_State;
		
	};
}