#pragma once
#include "UI_Time.h"

namespace jk
{
	class Image;
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
		float mTime_S;

	};
}