#pragma once
#include "jk_Gameobject.h"
#include "jk_Image.h"

namespace jk
{
	class Animator;
	class UI_Time : public Gameobject
	{
	public:
		UI_Time();
		~UI_Time();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		float Get_seconds() { return time_S; }
		float Get_minutes() { return time_M; }

	private:
		Image* mImage;
		float mTime;
		float time;

		float time_S; 
		float time_M;
	};
}