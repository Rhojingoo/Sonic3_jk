#pragma once
#include "jk_Gameobject.h"
#include "jk_Boss.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
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

