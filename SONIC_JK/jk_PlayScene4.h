#pragma once
#include "jk_Scene.h"


namespace jk
{
	class Image;
	class Sound;
	class Deatht_line_act6;
	class Ending_boss;
	class Boss_trash;
	class act6_sky1;
	class Third_Boss;
	class Boss_Arm;
	class finall_stage;
	class Second_Boss;
	class Robotnic_machine;
	class First_Boss;
	class Pixel_Ground;
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
		Pixel_Ground* playgr;
		Sonic* mSonic;
		Tails* mTails;
		First_Boss* mFirst_Boss;
		Robotnic_machine* mRobotnic_machine;
		Second_Boss* mSecond_Boss;	
		finall_stage* mFinall_stage;
		Boss_Arm* mBoss_Arm;
		Third_Boss* mThird_Boss;
		act6_sky1* mAct6_sky1;
		Boss_trash* mBoss_trash;
		Ending_boss* mEnding_boss;
		Deatht_line_act6* mDeatht_line_act6;


	private:
		Sound* mBoss_start;
		Sound* mAct6_music;
		Sound* mRocket_Start;
		Sound* mLast_Boss_f;
		Sound* mStage_bomb;
		Sound* mEnding;


		//ø’√‚«ˆ
		int mCamera_Switch;
		int mCheck_boss;
		int mFrame_check;
		int mBoss_Death_point;
		int mMap_lotation;
		int mBOSS2_Start;
		int mBOSS3_Start;
		int mBoss_end;
		int mArm_lotaion;
		int mDir;
		int mCheck_map;
		float mTime;
	};
}