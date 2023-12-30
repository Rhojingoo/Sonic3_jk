#pragma once
#include "UI_Time.h"

namespace jk
{
	class Image;
	class Animator;
	class UI_Time_minutes : public UI_Time
	{
	public:
		UI_Time_minutes(Gameobject* owner);
		~UI_Time_minutes();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Gameobject* mOwner;
		UI_Time* minutes;
		Image* mImage;
		float mTime_M;
	};
}