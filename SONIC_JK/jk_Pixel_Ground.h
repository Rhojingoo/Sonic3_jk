#pragma once
#include "jk_Gameobject.h"

namespace jk
{
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


		int GetCicle_piece() { return Circle_pice; }		
		virtual int GetgroundCh() {return mRotationcheck;}


		void Set_Circle_Center(Vector2 check) { Circle1_Center = check; }
		void Set_Circlecheck(int cir_check) { Circlecheck = cir_check; }
		void SetPlayer(class Sonic* player, class Tails* player2) { mPlayer = player, mPlayer2 = player2; }
		
		void SetLotation(const int rotaion) {	mRotationcheck = rotaion;}

		class Image* GetGroundImage();
		class Image* GetGroundImage2();
		class Image* GetGroundImage3();
		class Image* GetGroundImage4();


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

		void Set_map_check(int chek) { map_chek = chek; }
		int Get_map_check() { return map_chek; }
	

	private:		
		class Sonic* mPlayer;
		class Tails* mPlayer2;
		class Transform* mPlayerTR;
		class Transform* mPlayer_Tails_TR;
		Rigidbody* mPlayerRigidBody;
		Rigidbody* mRigidbody_Tails;
		int SonicDir;
		int TailsDir;
		
	private:
		int GROUND;		
		int LOOPENTERCOLOR;	
		int LOOPAFTERHALF;	
		int Circlecheck;

	private:
		//act1-1 이미지
		class Image* Ground_Image;
		class Image* Cicle_Rturn;
		class Image* Cicle_Lturn;		
		//act1-2 이미지
		class Image* Ground_Image2;
		class Image* Cicle_Rturn2;
		class Image* Cicle_Lturn2;
		//act1-3 이미지
		class Image* Ground_Image3;
		//act6 이미지
		class Image* Ground_Image4;

	private:
		int mDirect;
		int Circle_pice;	
		int mRotationcheck;		
		int WallCheck;
		bool LoopStoneMeet = false;
		class Collider* mCollider;
		int map_chek;
		int groundcheck;

	private://외부에서 서클센터바꾸기		
		Vector2 Circle1_Center;
		Vector2 Circle1_Center2;
	};
}
