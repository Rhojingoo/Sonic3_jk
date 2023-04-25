#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Animator;
	class Boss_Run : public Gameobject
	{
	public:
		enum class eBossState
		{	
			Move,
		};

		Boss_Run(Gameobject* owner);
		~Boss_Run();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:			
		void move();

	private:
		Image* mImage;
		Animator* mAnimator;
		Vector2 mCenterpos;		
		Vector2 pos;

		float mMonspeed;
		float mMonmaxdistance;
		int mDir;
		float fDist;
		eBossState mState;	
		float time;		

	};
}

