#pragma once
#include "jk_Scene.h"


namespace jk
{
	class EmeraldSonic;
	class MinigameScene : public Scene
	{
	public:
		MinigameScene();
		~MinigameScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void CreateBlending();

	private:
		EmeraldSonic* emsonic;
	};
}