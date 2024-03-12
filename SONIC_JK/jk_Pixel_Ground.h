#pragma once
#include "jk_Gameobject.h"

namespace jk
{
	class Image;
	class Rigidbody;
	class Pixel_Ground : public Gameobject
	{
	public:
		Pixel_Ground();
		virtual ~Pixel_Ground();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hd);
		virtual void Realease();


		int GetCicle_piece() { return mCircle_pice; }		
		virtual int GetgroundCh() {return mRotationcheck;}


		void Set_Circle_Center(Vector2 check) { mCircle1_Center = check; }
		void Set_Circlecheck(int cir_check) { mCirclecheck = cir_check; }
		void SetPlayer(class Sonic* player, class Tails* player2) { mPlayer = player, mPlayer2 = player2; }
		
		void SetLotation(const int rotaion) {	mRotationcheck = rotaion;}

		Image* GetGroundImage();
		Image* GetGroundImage2();
		Image* GetGroundImage3();
		Image* GetGroundImage4();


	public:
		void Loop_Angle();
		void Loop_Enter();
		void Loop_Stone();
		void CheckTerrian();
		void CheckGroundCollision(Vector2& playerPos, float xOffset, float yOffset, Image* ground, Transform* Playertr, Rigidbody* PlayerRg);
		void CheckCeillingCollision(Vector2& playerPos, float xOffset, float yOffset, Vector2 velocityChange, Image* ground);
		void CheckWallCollision(Vector2& playerPos, float xOffset, float yOffset, Vector2 velocityChange, int direction, Image* ground);
		
		void CheckLoopStartColl_R();
		void CheckLoopHalfColl_R();

		void Check_LoopStoneEnter_R();
		void Check_MidLoopStone_R();
		void Check_FinalLoopStone_R();


		void CheckLoopStartColl_L();
		void CheckLoopHalfColl_L();
		
		void Check_LoopStoneEnter_L();
		void Check_MidLoopStone_L();
		void Check_FinalLoopStone_L();

		void Set_map_check(int chek) { mMap_Check = chek; }
		int Get_map_check() { return mMap_Check; }
	

	private:		
		class Sonic* mPlayer;
		class Tails* mPlayer2;
		class Transform* mPlayerTR;
		class Transform* mPlayer_Tails_TR;
		Rigidbody* mPlayerRigidBody;
		Rigidbody* mRigidbody_Tails;
		int mSonicDir;
		int mTailsDir;
		
	private:
		int mGROUND;		
		int mLOOPENTERCOLOR;	
		int mLOOPAFTERHALF;	
		int mCirclecheck;

	private:
		//act1-1 이미지
		class Image* mGround_Image;
		class Image* mCicle_Rturn;
		class Image* mCicle_Lturn;		
		//act1-2 이미지
		class Image* mGround_Image2;
		class Image* mCicle_Rturn2;
		class Image* mCicle_Lturn2;
		//act1-3 이미지
		class Image* mGround_Image3;
		//act6 이미지
		class Image* mGround_Image4;

	private:
		int mDirect;
		int mCircle_pice;	
		int mRotationcheck;		
		int WallCheck;
		bool mLoopStoneMeet = false;
		class Collider* mCollider;
		int mMap_Check;
		int mGroundCheck;
		const int Right = 1;
		const int Left = -1;

	private://외부에서 서클센터바꾸기		
		Vector2 mCircle1_Center;
		Vector2 mCircle1_Center2;
	};
}
