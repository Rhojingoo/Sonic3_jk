#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Choice_select : public Gameobject
	{
	public:
		Choice_select();
		~Choice_select();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		Animator* mAnimator;	
		int Select_state;		
	};
}