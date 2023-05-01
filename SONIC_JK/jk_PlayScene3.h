#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{
	class show_bomb;
	class boss_bomber;
	class Add_force;
	class Ground;
	class Boss;
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
		void Create_Boomber_show();
		void Create_Boomber_bombing(float a, float b);


	private:
		Ground* playgr;
		Sonic* mSonic;
		Tails* tails;
		Boss* mBoss;
		boss_bomber* mBomber;
		show_bomb* bomb;
		Add_force* add_force[9];
		int dir;
		int check_map;


		//ø’√‚«ˆ
		int Camera_Switch;
		int check_boss;
		int frame_check;
		int boss_death;
		int boomber;
		int bomb_check;
		int boss_appear;
	};
}