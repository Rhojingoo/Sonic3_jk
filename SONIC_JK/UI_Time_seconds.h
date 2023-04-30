#pragma once
#include "UI_Time.h"
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class UI_Time_seconds : public UI_Time
	{
	public:
		UI_Time_seconds(Gameobject* owner);
		~UI_Time_seconds();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		UI_Time* seconds;
		Image* mImage;

		float time_S;

	};
}