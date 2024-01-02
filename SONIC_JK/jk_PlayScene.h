#pragma once
#include "jk_Scene.h"


namespace jk
{
	class Image;
	class Sound;
	class Tails;
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
		Tails* mTails;
		Sound* mAct1_music;
		Sound* mMiniboss1;
		Sound* mAct2_music;

		int mCamera_Switch;
		int mDir;
		int mCheck_minibos;
		int mFrame_check;
	};
}