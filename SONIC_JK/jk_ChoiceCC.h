#pragma once
#include "jk_Gameobject.h"
#include "jk_BackGround.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class ChoiceCC : public BackGround
	{
	public:
		ChoiceCC();
		~ChoiceCC();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;




	private:	
		Image* mImage1;	
		Animator* mAnimator;		
	};

}
