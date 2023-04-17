#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Rigidbody;
	class Ground : public Gameobject
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hd);
		virtual void Realease();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		int GetCicle_piece() { return Circle_pice; }		
		virtual int GetgroundCh() {return mRotationcheck;}

		void Set_Circle_Center(Vector2 check) { Circle1_Center = check; }
		void Set_Circlecheck(int cir_check) { Circlecheck = cir_check; }

		void SetPlayer(class Sonic* player, class Tails* player2) { mPlayer = player, mPlayer2 = player2; }

		class Image* GetGroundImage() 
		{ 
			if (!Ground_Image) 
				return nullptr;
			
			return Ground_Image;
		}


	public:
		void CheckGround();
		void CheckLoopEnter_R();
		void CheckLoopStoneEnter_R();
		void CheckLoopStoneSecond_R();
		void CheckLoopStoneGround_R();
		void CheckLoopHalfAfter_R();


		void CheckLoopStoneEnter_L();
		void CheckLoopStoneSecond_L();
		void CheckLoopStoneGround_L();
		void CheckLoopEnter_L();
		void CheckLoopHalfAfter_L();


		//void MonsterGround();

	private:		
		class Sonic* mPlayer;
		class Tails* mPlayer2;
		class Monster* mRino0;
		class Ring_Falling* mRing;

		class Transform* mPlayerTR;
		class Transform* mPlayer_Tails_TR;
		class Transform* mRino0_TR;
		class Transform* ring_TR;

		Rigidbody* mPlayerRigidBody;
		Rigidbody* mRigidbody_Tails;
		Rigidbody* mRigidbody_Rino0;
		Rigidbody* ring_rb;

		int SonicDir;
		int TailsDir;


		int Circlecheck;
		class Image* Ground_Image;
		class Image* Cicle_Rturn;
		class Image* Cicle_Lturn;
		int mDirect;
		int Circle_pice;
		int Circle_pice_Tails;
		int mRotationcheck;
		//외부에서 서클센터바꾸기
		Vector2 Circle1_Center;


		int WallCheck;

		class Collider* mCollider;

		//check가 1이라면 오른쪽중간 //check가 2라면 위로 //check가 3이상이라면 중간에서 안떨어짐 // check가 4라면 왼쪽위 //check가 5라면 원상복귀
	};
}
