#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"

namespace jk
{
	class Sound;
	class Ground;
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
		Ground* playgr;
		Sonic* mSonic;		
		Sound* Act2_music;
		Sound* Miniboss2;
		int dir;
		int check_map;


		//ø’√‚«ˆ
		int Camera_Switch;
		int check_minibos;
		int frame_check;

	};
}