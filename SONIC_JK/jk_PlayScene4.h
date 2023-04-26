#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{

	class finall_stage;
	class Second_Boss;
	class Robotnic_machine;
	class boss1_body;
	class Ground;
	class Sonic;
	class PlayScene4 : public Scene
	{
	public:
		PlayScene4();
		~PlayScene4();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void CreateBlending();
		void Create_Boss1();
		void Create_Boss2();



	private:
		Ground* playgr;
		Sonic* mSonic;
		boss1_body* boss_first;
		Robotnic_machine* fly_machine;
		Second_Boss* second_boss;
		finall_stage* stage_final;

		int dir;
		int check_map;


		//ø’√‚«ˆ
		int Camera_Switch;
		int check_boss;
		int frame_check;
		int Boss_Death_point;
		int map_lotation;




	};
}