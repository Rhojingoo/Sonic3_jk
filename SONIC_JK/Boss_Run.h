#pragma once
#include "jk_Boss.h"



namespace jk
{
	class Image;
	class Animator;
	class Boss_Run : public Boss
	{
	public:

		Boss_Run(Gameobject* owner);
		~Boss_Run();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void Set_Dir(int dir) { mDir = dir; }



	private:
		Image* mImage;
		Animator* mAnimator;		
		int mDir;
	};
}

