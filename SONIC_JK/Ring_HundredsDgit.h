#pragma once
#include "Ring_Point_Manager.h"
#include "jk_Gameobject.h"


namespace jk
{
	class Image;
	class Animator;
	class Ring_HundredsDgit : public Gameobject
	{
	public:
		Ring_HundredsDgit(Gameobject* owner);
		~Ring_HundredsDgit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		Ring_Point_Manager* mUnits;
		Image* mImage;
		int mHundredsDigit;
	};
}