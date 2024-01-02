#pragma once
#include "jk_Scene.h"


namespace jk
{
	class Image;
	class Sound;
	class Dead_line;
	class show_bomb;
	class boss_bomber;
	class Add_force;
	class Pixel_Ground;
	class Act1_Boss;
	class Tails;
	class Sonic;
	class PlayScene3 : public Scene
	{
	public:
		PlayScene3();
		~PlayScene3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;



		void CreateBlending();
		void Create_Boss_Apear();
		void Create_Boss();
		void Create_Deathtline();
		void Create_Boomber_show();
		void Create_Boomber_bombing(float a, float b);


	private:
		Pixel_Ground* mPixel_Ground;
		Sonic* mSonic;
		Tails* mTails;
		Act1_Boss* mBoss;
		boss_bomber* mBoss_bomber;
		show_bomb* mShow_bomb;
		Add_force* mAdd_force[9];
		Dead_line* mDead_line;

	private:
		Sound* mAct2_music;
		Sound* mAct6_music;
		Sound* mBoss_Sound;
		Sound* mBoss_start;

	private:
		int mDir;
		int mCheck_map;
		//ø’√‚«ˆ
		int Camera_Switch;
		int mCheck_boss;
		int mFrame_check;
		int mBoss_death;
		int mBoomber;
		int mBomb_check;
		int mBoss_appear;
	};
}