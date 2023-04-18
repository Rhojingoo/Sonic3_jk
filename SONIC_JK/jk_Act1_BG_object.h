#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class Act1_BG_object : public Gameobject
	{
	public:
		Act1_BG_object();
		~Act1_BG_object();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void Set_Owner(Gameobject* s_body) { mOwner = s_body; }


	private:
		Image* mImage;
		Sonic* mSonic;
		int Check_BG;
		Gameobject* mOwner;
		Vector2 mSonic_pos;
	};

}
