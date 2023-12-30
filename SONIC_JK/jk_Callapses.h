#pragma once
#include "jk_BackGround.h"


namespace jk
{
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
		class Image* mImage;	
		class Rigidbody* mRigidbody;	
		class Animator* mAnimator;
	};

}