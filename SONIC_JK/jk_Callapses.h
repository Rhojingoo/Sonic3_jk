#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"
#include "jk_SONIC.h"
#include "jk_Animator.h"

namespace jk
{
	class Rigidbody;
	class Animator;
	class Callapses : public BackGround
	{
	public:

		Callapses();
		~Callapses();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void death();


	private:
		Image* mImage;	
		Rigidbody* mRigidbody;	
		Animator* mAnimator;
	};

}