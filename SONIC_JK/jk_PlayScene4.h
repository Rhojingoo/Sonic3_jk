#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{

	class Ending_boss;
	class Boss_trash;
	class act6_sky1;
	class Third_Boss;
	class Boss_Arm;
	class finall_stage;
	class Second_Boss;
	class Robotnic_machine;
	class boss1_body;
	class Ground;
	class Tails;
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
		void Create_Boss3();
		void Last_Stage_bomb(float a, float b);
		void ending_boss();
		void boss_trash();



	private:
		Ground* playgr;
		Sonic* mSonic;
		Tails* mtails;
		boss1_body* boss_first;
		Robotnic_machine* fly_machine;
		Second_Boss* second_boss;	
		finall_stage* stage_final;
		Boss_Arm* boss_arm;
		Third_Boss* last_boss;
		act6_sky1* sky1;
		Boss_trash* trash;
		Ending_boss* end_boss;
	
		int dir;
		int check_map;


		//ø’√‚«ˆ
		int Camera_Switch;
		int check_boss;
		int frame_check;
		int Boss_Death_point;
		int map_lotation;
		int BOSS2_Start;
		int BOSS3_Start;
		int Boss_end;
		float time;
		int arm_lotaion;
	
	};
}