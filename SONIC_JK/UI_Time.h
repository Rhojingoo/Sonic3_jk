#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Image;
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

		float Get_seconds() { return mTime_S; }
		float Get_minutes() { return mTime_M; }

	private:
		Image* mImage;
		float mTime;
		float mTime2;

		float mTime_S; 
		float mTime_M;
	};
}