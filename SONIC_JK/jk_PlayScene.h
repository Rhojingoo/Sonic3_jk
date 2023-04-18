#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{
	class Sonic;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		
		void CreateBlending();
		void Create_Miniboss_show();

	private:
		Sonic* mSonic;
		int Camera_Switch;
		int dir;
		int check_minibos;
	};
}