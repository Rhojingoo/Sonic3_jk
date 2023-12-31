#pragma once
#include "jk_Effect.h"

namespace jk
{
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
		int Get_map_check() {return mMap_check;}

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


	private:
		void move();		
		void attack();
		void death();


	private:
		class Image* mImage;
		class Animator* mAnimator;
		class Sound* mAct1_music;
		class Sound* mMiniboss1;
		class Sound* mFire_show;
		class Sound* mAct2_music;


	private:
		Vector2 mPos;
		Vector2 mCenterpos;	
		float fDist;
		float mMonspeed;
		float mMonmaxdistance;
		float time;	
		int mDir;
		eState mState;
	
		int mShoot;	
		int mMap_check;
	};
}
