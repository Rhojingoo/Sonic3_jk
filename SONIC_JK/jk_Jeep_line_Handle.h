#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Jeep_line_Handle : public BackGround
	{
	public:

		Jeep_line_Handle();
		~Jeep_line_Handle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetCenterpos(Vector2 pos) { mCenterpos = pos; }
		void SetAngle(float ang) { angle = ang; }
		void SetDirect(int dir) { mDir_x = dir; }
		int Getjeepline_state() { return Jeepline_state; }

		int GetDir() {	return mDir_x;}
			

	private:
		Image* mImage;
		Animator* mAnimator;

	private:
		Vector2 mCenterpos;
		int mDir_x;
		int Jeepline_state;
		float angle;
	};

}