#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class act6_sky7 : public Gameobject
	{
	public:
		act6_sky7();
		~act6_sky7();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;

	};

}