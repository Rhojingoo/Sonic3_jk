#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Ending : public Gameobject
	{
	public:
		Ending();
		~Ending();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};
}
