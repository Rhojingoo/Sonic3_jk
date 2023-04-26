#pragma once
#include "jk_Gameobject.h"
#include "jk_SONIC.h"
#include "jk_Image.h"
#include "jk_Time.h"


namespace jk
{
	class Rigidbody;
	class Animator;
	class Third_Boss : public Gameobject
	{
	public:
		enum class eBossState
		{
			Start,
			Left_Cross,
			Right_Cross,
			Left,
			Right,

			Grap_R,
			Grap_L,

	


			Death
		};

		Third_Boss();
		~Third_Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;	

		int Get_mDir() { return mDir; }
		int Get_Hurt() { return Hur_check; }
		void Set_Grap(int grap) { Grap_pattern = grap; }


	private:
		void start();
		void L_cross();
		void R_cross();
		void left();
		void right();

		void grap_R();
		void grap_L();

		void Hurt();

		void death();


	private:
		Image* mImage;
		Image* mImage1;
		Animator* mAnimator;
		Rigidbody* mRigidbody;


		Vector2 mCenterpos;
		Vector2 pos;
		float mSpeed;
		int mDir;
		float Up_Down;



		Sonic::eSonicState sonicState;
		eBossState mState;

		float time;
		int Boss_cross_change;
		int Damege_check;
		int Boomb_point;
		int Grap_pattern;
		int Hur_check;

	};
}
