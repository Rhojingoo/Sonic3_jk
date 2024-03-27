#pragma once
#include "jk_Scene.h"

namespace jk
{
	class Image;
	class Sound;
	class LoadingScene : public Scene
	{
	public:
		LoadingScene();
		~LoadingScene();

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


