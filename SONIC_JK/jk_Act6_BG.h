#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class jk_Act6_BG : public Gameobject
	{
	public:
		jk_Act6_BG();
		~jk_Act6_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
			

	private:
		Image* mImage;
		Sonic* mSonic;
		int Check_BG;
		Gameobject* mOwner;
		Vector2 mSonic_pos;
	};

}