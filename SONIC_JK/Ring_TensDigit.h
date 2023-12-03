#pragma once
#include "Ring_Point_Manager.h"
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class Ring_TensDigit : public Gameobject
	{
	public:
		Ring_TensDigit(Gameobject* owner);
		~Ring_TensDigit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		Ring_Point_Manager* Units;
		Image* mImage;
		float TensDigit;
	};
}