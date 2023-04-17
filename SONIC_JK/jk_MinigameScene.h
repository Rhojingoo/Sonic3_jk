#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{
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
		Image* mScenImage;
	};
}