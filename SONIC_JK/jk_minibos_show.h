#pragma once
#include "jk_Gameobject.h"
#include "jk_Effect.h"
#include "jk_Image.h"
#include "jk_Time.h"
#include "jk_Sound.h"


namespace jk
{
	class Animator;
	class minibos_show : public Effect
	{
	public:
		enum class eState
		{
			Move,
			Attack,	
			Death
		};


		minibos_show();
		~minibos_show();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;
		int Get_map_check() {return map_check;}

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		void move();		
		void attack();
		void death();


	private:
		Image* mImage;
		Animator* mAnimator;
		Sound* Act1_music;
		Sound* Miniboss1;
		Sound* Fire_show;
		Sound* Act2_music;


	private:
		Vector2 pos;
		Vector2 mCenterpos;	
		float fDist;
		float mMonspeed;
		float mMonmaxdistance;
		float time;	
		int mDir;
		eState mState;
	
	private:
		int shoot;	
		int map_check;
	};
}
