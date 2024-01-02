#pragma once
#include "jk_Scene.h"


namespace jk
{
	class Image;
	class Sound;
	class Pixel_Ground;
	class Snake;
	class Sonic;
	class PlayScene2 : public Scene
	{
	public:
		PlayScene2();
		~PlayScene2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		
	

		void CreateBlending();
		void Create_Miniboss();



	private:
		Pixel_Ground* mPixel_Ground;
		Sonic* mSonic;		
		Snake* mSnake;
		Sound* mAct2_music;
		Sound* mMiniboss2;
		int mDir;
		int mCheck_map;


		//ø’√‚«ˆ
		int mCamera_Switch;
		int mCheck_minibos;
		int mFrame_check;

	};
}