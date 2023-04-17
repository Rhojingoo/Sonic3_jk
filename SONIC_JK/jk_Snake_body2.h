#pragma once
#include "jk_Gameobject.h"
#include "jk_Snake_Body.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{	
	class Animator;
	class Snake_body2 : public Gameobject
	{
	public:
		enum class eSnake
		{
			Right,
			Left,
			Deth
		};

		Snake_body2();
		~Snake_body2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		eSnake Get_Snake_state() { return mState; }
		void Set_Snake_body_third(Gameobject* s_body) { snake_body = s_body; }
		virtual Vector2 GetPrevPos() override;

	private:
			
		void right();
		void left();
		void deth();

	private:
		Gameobject* mOwner;
		Image* mImage;
		Animator* mAnimator;
		eSnake mState;
		Vector2 pos;
		Gameobject* snake_body;
		Vector2 prevPos;

		Snake_Body::eSnake snake_body_state;
	};
}