#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{
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
		void Create_Boss();



	private:
		Ground* playgr;
		Sonic* mSonic;
		Tails* tails;
		Boss* mBoss;
		int dir;
		int check_map;


		//ø’√‚«ˆ
		int Camera_Switch;
		int check_boss;
		int frame_check;
		int boss_death;
	};
}