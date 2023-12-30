#include "jk_Pixel_Ground.h"

#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"

#include "jk_Input.h"
#include "jk_Camera.h"

#include "jk_SONIC.h"
#include "jk_Tails.h"

// 땅, 원 진입(300도 ~ 89도), 원의 중간 이후(90도 ~ 약240도) 
//#define mGROUND			0
//#define mLOOPENTERCOLOR	1
//#define mLOOPAFTERHALF		2

//#define GROUNDCOLOR						RGB(0, 0, 0)
//#define WALLCOLOR						RGB(0, 12, 123)
//#define FLYLCOLOR						RGB(51, 102, 102)
//
//#define STONEGREY_LOOPENTER				RGB(127, 127, 127) 
//#define STONEORANGE_LOOPHALF			RGB(255, 127, 0)
//#define STONERED_LOOPENTER				RGB(255, 0, 0)
//
//#define GROUNDYELLO_LOOPCOURSE_RIGHT	RGB(255, 255, 0)
//#define GROUNDBLUE_LOOPCOURSE_LEFT		RGB(0, 0, 255)


namespace jk
{
	Vector2 Circle1_Top = Vector2{ 20229.f,3127.f };
	float Radian_Cicle1 = 0.0f;
	float Degree_Cicle1 = 0.0f;


	float Radian_Circle1_Tails = 0.0f;
	float Degree_Circle1_Tails = 0.0f;

	Pixel_Ground::Pixel_Ground()
		: mPlayer(nullptr)
		, mPlayer2(nullptr)
		, mPlayerTR(nullptr)
		, mPlayer_Tails_TR(nullptr)
		, mPlayerRigidBody(nullptr)
		, mRigidbody_Tails(nullptr)
		, mSonicDir(0)
		, mTailsDir(0)

		, mGROUND(0)
		, mLOOPENTERCOLOR(1)
		, mLOOPAFTERHALF(2)

		, mCirclecheck(1)
		//act1-1
		, mGround_Image(nullptr)
		, mCicle_Rturn(nullptr)
		, mCicle_Lturn(nullptr)
		//act1-2
		, mGround_Image2(nullptr)
		, mCicle_Rturn2(nullptr)
		, mCicle_Lturn2(nullptr)
		//act1-3
		, mGround_Image3(nullptr)
		//act6
		, mGround_Image4(nullptr)

		, mDirect(1)
		, mCircle_pice(0)
		, mRotationcheck(0)

		, mCircle1_Center(0.f, 0.f)
		, mCircle1_Center2(0.f, 0.f)

		, WallCheck(0)
		, mLoopStoneMeet(false)
		, mMap_Check(0)
		, mGroundCheck(0)
		, mCollider(nullptr)

	{
	}

	Pixel_Ground::~Pixel_Ground()
	{
	}

	void Pixel_Ground::Initialize()
	{
		mGround_Image = Resources::Load<Image>(L"Ground_Image", L"..\\Resources\\Ground_Image.bmp");
		mCicle_Rturn = Resources::Load<Image>(L"Cicle_Rturn", L"..\\Resources\\Cicle_Rturn.bmp");
		//mCicle_Lturn = Resources::Load<Image>(L"mCicle_Lturn", L"..\\Resources\\mCicle_Lturn.bmp");
		mCircle1_Center = Vector2{ 20229.f,3406.f };
		mCircle1_Center2 = Vector2{ 9195.f, 3705.f };

		mGround_Image2 = Resources::Load<Image>(L"Ground_Image2", L"..\\Resources\\Ground_Act1_2.bmp");
		mCicle_Rturn2 = Resources::Load<Image>(L"Cicle_Rturn2", L"..\\Resources\\ActBG_1_2\\Cicle_Rturn2.bmp");
		//mCicle_Lturn2 = Resources::Load<Image>(L"mCicle_Lturn2", L"..\\Resources\\ActBG_1_2\\mCicle_Lturn2.bmp");

		mGround_Image3 = Resources::Load<Image>(L"Ground_Image3", L"..\\Resources\\ActBG_1_3\\Ground_Act1_3.bmp");
		mGround_Image4 = Resources::Load<Image>(L"Ground_Image4", L"..\\Resources\\ActBG_6\\act 6-boss_ground.bmp");

		Gameobject::Initialize();
	}

	void Pixel_Ground::Update()
	{

		mPlayerTR = mPlayer->GetComponent<Transform>();
 
		Vector2 Player_Position = mPlayerTR->GetPos();
		mSonicDir = mPlayer->GetSonicDir();

		//소닉 TR, RG설정
		if ((nullptr == mPlayerTR) || (nullptr == mPlayerRigidBody))
		{
			if (!mPlayer)
				return;

			mPlayerTR = mPlayer->GetComponent<Transform>();
			mPlayerRigidBody = mPlayer->GetComponent<Rigidbody>();

		}

		//테일즈 TR, RG설정
		if ((nullptr == mPlayer_Tails_TR) || (nullptr == mRigidbody_Tails))
		{
			if (!mPlayer2)
				return;

			mPlayer_Tails_TR = mPlayer2->GetComponent<Transform>();
			mRigidbody_Tails = mPlayer2->GetComponent<Rigidbody>();
		}

		CheckTerrian();

		Loop_Angle();
	
		Loop_Enter();

		Loop_Stone();		

		Gameobject::Update();
	}

	void Pixel_Ground::Render(HDC hdc)
	{
		Gameobject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 mpos = pos - (Camera::CaluatePos(pos) - pos);

		if (mMap_Check == 0)
		{
			if (Input::GetKey(eKeyCode::Q))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, mGround_Image->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
			if (Input::GetKey(eKeyCode::W))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, mCicle_Rturn->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
		}

		if (mMap_Check == 1)
		{
			if (Input::GetKey(eKeyCode::Q))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, mGround_Image2->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
			if (Input::GetKey(eKeyCode::W))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, mCicle_Rturn2->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
		}

		if (mMap_Check == 2)
		{
			if (Input::GetKey(eKeyCode::Q))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, mGround_Image3->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
		}

		if (mMap_Check == 3)
		{
			if (Input::GetKey(eKeyCode::Q))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, mGround_Image4->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
		}
	}

	void Pixel_Ground::Realease()
	{
		Gameobject::Release();
	}


	Image* Pixel_Ground::GetGroundImage()
	{		
		if (!mGround_Image)
			return nullptr;

		return mGround_Image;		
	}

	Image* Pixel_Ground::GetGroundImage2()
	{
		if (!mGround_Image2)
			return nullptr;

		return mGround_Image2;
	}

	Image* Pixel_Ground::GetGroundImage3()
	{
		if (!mGround_Image3)
			return nullptr;

		return mGround_Image3;
	}

	Image* Pixel_Ground::GetGroundImage4()
	{
		if (!mGround_Image4)
			return nullptr;

		return mGround_Image4;
	}

	//#define NO_DEBUG_PRINT 디버그모드확인 세컨드스톤만나는위치확인
	//#ifdef NO_DEBUG_PRINT
	//#define DEBUG_PRINT
	//#else
	//	static void _PrintDebugString(const WCHAR* format, ...) {
	//		WCHAR buf[1024];
	//		va_list vaList;
	//		va_start(vaList, format);
	//		_vsnwprintf_s(buf, sizeof(buf), format, vaList);
	//		va_end(vaList);
	//		OutputDebugStringW(buf);
	//	}
	//	static void _PrintDebugString(const char* format, ...) {
	//		char buf[1024];
	//		va_list vaList;
	//		va_start(vaList, format);
	//		_vsnprintf_s(buf, sizeof(buf), format, vaList);
	//		va_end(vaList);
	//		OutputDebugStringA(buf);
	//	}
	//#define DEBUG_PRINT _PrintDebugString
	//#endif


	void Pixel_Ground::Loop_Angle()
	{
		Radian_Cicle1 = atan2(mCircle1_Center.y - mPlayerTR->GetPos().y, mCircle1_Center.x - mPlayerTR->GetPos().x);
		Degree_Cicle1 = Radian_Cicle1 * (180.f / static_cast<float>(PI));
		if (Degree_Cicle1 <= -67.5f && Degree_Cicle1 > -112.5f)//중앙하부 
		{
			mCircle_pice = 0;
		}
		if (Degree_Cicle1 <= -112.5f && Degree_Cicle1 > -157.5f)//오른쪽하부 
		{
			mCircle_pice = 1;
		}
		if (Degree_Cicle1 <= -157.5f || (Degree_Cicle1 >= 157.5f && Degree_Cicle1 <= 180.f))// 오른쪽옆
		{
			mCircle_pice = 2;
		}
		if (Degree_Cicle1 >= 112.5f && Degree_Cicle1 < 157.5f)// 오른쪽상부
		{
			mCircle_pice = 3;
		}
		if (Degree_Cicle1 >= 67.5f && Degree_Cicle1 < 112.5f)// 중앙상부
		{
			mCircle_pice = 4;
		}
		if (Degree_Cicle1 >= 22.5f && Degree_Cicle1 < 67.5f)// 왼쪽상부
		{
			mCircle_pice = 5;
		}
		if ((Degree_Cicle1 <= 0.f && Degree_Cicle1 > -22.5f) || (Degree_Cicle1 >= 0.f && Degree_Cicle1 < 22.5f))// 왼쪽옆
		{
			mCircle_pice = 6;
		}
		if (Degree_Cicle1 <= -22.5f && Degree_Cicle1 > -67.5f)//왼쪽하부 
		{
			mCircle_pice = 7;
		}
	}

	void Pixel_Ground::Loop_Enter()
	{
		Vector2 playerPos = mPlayerTR->GetPos();
		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF color_Right = static_cast<int>(selectedImage->GetPixel(static_cast<int>(playerPos.x + 100.f), static_cast<int>(playerPos.y + 50.f)));
		if (mRotationcheck == GROUNDCOLOR && color_Right == GROUNDBLUE_LOOPCOURSE_LEFT)
		{
			mDirect = 1;
		}

		COLORREF  color_Left = static_cast<int>(selectedImage->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y + 50.f)));
		if (mRotationcheck == GROUNDCOLOR && color_Left == GROUNDYELLO_LOOPCOURSE_RIGHT)
		{
			mDirect = -1;
		}	
	}


	//if (mMap_Check == 0)
	//{
	//	COLORREF color_Right = static_cast<int>(mCicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 100.f), static_cast<int>(playerPos.y + 50.f)));
	//	if (mRotationcheck == GROUNDCOLOR && color_Right == GROUNDBLUE_LOOPCOURSE_LEFT)
	//	{
	//		mDirect = 1;
	//	}
	//	COLORREF  color_Left = static_cast<int>(mCicle_Rturn->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y + 50.f)));
	//	if (mRotationcheck == GROUNDCOLOR && color_Left == GROUNDYELLO_LOOPCOURSE_RIGHT)
	//	{
	//		mDirect = -1;
	//	}
	//}
	//if (mMap_Check == 1)
	//{
	//	COLORREF color_Right = static_cast<int>(mCicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + 100.f), static_cast<int>(playerPos.y + 50.f)));
	//	if (mRotationcheck == GROUNDCOLOR && color_Right == GROUNDBLUE_LOOPCOURSE_LEFT) // Input::GetKey(eKeyCode::RIGHT) &&
	//	{
	//		mDirect = 1;
	//	}
	//	COLORREF  color_Left = static_cast<int>(mCicle_Rturn2->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y + 50.f)));
	//	if (mRotationcheck == GROUNDCOLOR && color_Left == GROUNDYELLO_LOOPCOURSE_RIGHT)// && Input::GetKey(eKeyCode::LEFT)
	//	{
	//		mDirect = -1;
	//	}
	//}




	void Pixel_Ground::Loop_Stone()
	{
		if (mDirect == 1)
		{
			if (mCirclecheck == 1)
			{
				Check_LoopStoneEnter_R();
			}
			if (mRotationcheck == mLOOPENTERCOLOR)
			{
				CheckLoopStartColl_R();
			}
			if (mRotationcheck == mLOOPENTERCOLOR)
			{
				Check_MidLoopStone_R();
			}
			if (mRotationcheck == mLOOPAFTERHALF)
			{
				CheckLoopHalfColl_R();
			}
			if (mCirclecheck == -1)
			{
				Check_FinalLoopStone_R();
			}
		}
		else if (mDirect == -1)
		{
			if (mCirclecheck == -1)
			{
				Check_LoopStoneEnter_L();
			}
			if (mRotationcheck == mLOOPAFTERHALF)
			{
				CheckLoopStartColl_L();
			}
			if (mRotationcheck == mLOOPAFTERHALF)
			{
				Check_MidLoopStone_L();
			}
			if (mRotationcheck == mLOOPENTERCOLOR)
			{
				CheckLoopHalfColl_L();
			}	
			if (mCirclecheck == 1)
			{
				Check_FinalLoopStone_L();
			}
		}
	}

	void Pixel_Ground::CheckTerrian()
	{
		if (mRotationcheck != mGROUND)
			return;

		Vector2 playerPos = mPlayerTR->GetPos();
		Vector2 playerPos_Tails = mPlayer_Tails_TR->GetPos();
		float Xrevice = 40.0f;
		float Yrevice = 100.0f;
		float Xrevice_side = 0.0f;
		float Yrevice_side = 50.0f;
		
		if (mMap_Check == 0)////////////소닉 & 테일즈 픽셀체크 Act1-1//////////
		{		
			CheckGroundCollision(playerPos, Xrevice, Yrevice, mGround_Image, mPlayerTR, mPlayerRigidBody);					// 소닉땅체크	
			CheckGroundCollision(playerPos_Tails, Xrevice, Yrevice, mGround_Image, mPlayer_Tails_TR, mRigidbody_Tails);			// 테일즈땅체크		
			CheckCeillingCollision(playerPos,40.f, 20.f, Vector2{ mPlayerRigidBody->GetVelocity().x,0.f }, mGround_Image);   // 소닉위쪽벽 체크
			CheckWallCollision(playerPos, 80.f, Yrevice_side, Vector2{ 0.f, 0.f }, -1, mGround_Image);						// 소닉오른쪽 벽체크	
			CheckWallCollision(playerPos, 0.f, Yrevice_side, Vector2{ 0.f, 0.f }, 1, mGround_Image);							// 소닉왼쪽 벽체크		

			//FLY통
			COLORREF player_Down_Side_PosColor = mCicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 100.f));
			if (player_Down_Side_PosColor == FLYLCOLOR)
			{
				mPlayerRigidBody->SetGround(true);
				while (player_Down_Side_PosColor == FLYLCOLOR)
				{
					playerPos.y -= 1;
					player_Down_Side_PosColor = mCicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 100.f));
					//WallCheck = 1;
				}
				mPlayerTR->SetPos(playerPos);				
			}
		}		
		if (mMap_Check == 1)////////////소닉 & 테일즈 픽셀체크 Act1-2//////////
		{
			CheckGroundCollision(playerPos, Xrevice, Yrevice, mGround_Image2, mPlayerTR, mPlayerRigidBody);					// 소닉땅체크	
			CheckGroundCollision(playerPos_Tails, Xrevice, Yrevice, mGround_Image2, mPlayer_Tails_TR, mRigidbody_Tails);			// 테일즈땅체크		
			CheckCeillingCollision(playerPos, 40.f, 20.f, Vector2{ mPlayerRigidBody->GetVelocity().x,0.f }, mGround_Image2); // 소닉위쪽벽 체크
			CheckWallCollision(playerPos, 80.f, Yrevice_side, Vector2{ 0.f, 0.f }, -1, mGround_Image2);						// 소닉오른쪽 벽체크		
			CheckWallCollision(playerPos, 0.f, Yrevice_side, Vector2{ 0.f, 0.f }, 1, mGround_Image2);						// 소닉왼쪽 벽체크		
		}		
		if (mMap_Check == 2)////////////소닉 & 테일즈 픽셀체크 Act1-3//////////
		{
			Xrevice_side = 0.0f;
			Yrevice_side = 120.0f;
			CheckGroundCollision(playerPos, Xrevice, Yrevice, mGround_Image3, mPlayerTR, mPlayerRigidBody);					// 소닉땅체크			
			CheckGroundCollision(playerPos_Tails, Xrevice, Yrevice, mGround_Image3, mPlayer_Tails_TR, mRigidbody_Tails);		// 테일즈땅체크		
			CheckCeillingCollision(playerPos, 40.f, 20.f, Vector2{ mPlayerRigidBody->GetVelocity().x,0.f }, mGround_Image3); // 소닉위쪽벽 체크
			//CheckWallCollision(playerPos, 80.f, Yrevice_side, Vector2{ 0.f, 0.f }, -1, mGround_Image3);// 오른쪽 벽체크		
			//CheckWallCollision(playerPos, 0.f, Yrevice_side, Vector2{ 0.f, 0.f }, 1, mGround_Image3);	// 왼쪽 벽체크		

			//오른쪽벽 	
			COLORREF player_R_Side_PosColor = mGround_Image3->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_R_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Right = mGround_Image3->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Right == WALLCOLOR)
				{
					while (color_Push_Right == WALLCOLOR)
					{
						playerPos.x -= 1;
						color_Push_Right = mGround_Image3->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			//왼쪽벽
			COLORREF player_L_Side_PosColor = mGround_Image3->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_L_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Left = mGround_Image3->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Left == WALLCOLOR)
				{
					while (color_Push_Left == WALLCOLOR)
					{
						playerPos.x += 1;
						playerPos.y += 1;
						color_Push_Left = mGround_Image3->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
		}		
		if (mMap_Check == 3)////////////소닉 & 테일즈 픽셀체크 Act6//////////
		{
			CheckGroundCollision(playerPos, Xrevice, Yrevice, mGround_Image4, mPlayerTR, mPlayerRigidBody);					// 소닉땅체크			
			CheckGroundCollision(playerPos_Tails, Xrevice, Yrevice, mGround_Image4, mPlayer_Tails_TR, mRigidbody_Tails);		// 테일즈땅체크			
			CheckCeillingCollision(playerPos, 40.f, 20.f, Vector2{ mPlayerRigidBody->GetVelocity().x,0.f }, mGround_Image4); // 소닉위쪽벽 체크
			CheckWallCollision(playerPos, 80.f, Yrevice_side, Vector2{ 0.f, 0.f }, -1, mGround_Image4);						// 소닉오른쪽 벽체크		
			CheckWallCollision(playerPos, 0.f, Yrevice_side, Vector2{ 0.f, 0.f }, 1, mGround_Image4);						// 소닉왼쪽 벽체크		
		}		
	}
	void Pixel_Ground::CheckGroundCollision(Vector2& playerPos, float xOffset, float yOffset, Image* ground, Transform* Playertr, Rigidbody* PlayerRg)
	{
		COLORREF playerFootPosColor = ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y + yOffset));

		bool isJumpingOrHurt = mPlayer->Getsonicstate() == Sonic::eSonicState::Jump || mPlayer->Getsonicstate() == Sonic::eSonicState::Hurt || mPlayer->Getsonicstate() == Sonic::eSonicState::Spring_Jump;
		mGroundCheck = isJumpingOrHurt ? 2 : 20;
		playerFootPosColor = ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y + yOffset + mGroundCheck));
		
		if (playerFootPosColor == GROUNDCOLOR)
		{
			playerPos.y += mGroundCheck - 1;
			while (ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y + yOffset)) == GROUNDCOLOR)
			{
				playerPos.y--;
			}
			Playertr->SetPos(playerPos);
			PlayerRg->SetGround(true);
		}
		else
		{
			PlayerRg->SetGround(false);
		}
	}
	void Pixel_Ground::CheckCeillingCollision(Vector2& playerPos, float xOffset, float yOffset, Vector2 velocityChange, Image* ground)
	{
		COLORREF Ceilling_PosColor = ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y - yOffset));
		if (Ceilling_PosColor == WALLCOLOR)
		{
			while (Ceilling_PosColor == WALLCOLOR)
			{
				playerPos.y += 1;
				Ceilling_PosColor = ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y - yOffset));
				mPlayerRigidBody->SetVelocity(Vector2{ velocityChange });
			}
			mPlayerTR->SetPos(playerPos);
		}

	}
	void Pixel_Ground::CheckWallCollision(Vector2& playerPos, float xOffset, float yOffset, Vector2 velocityChange, int direction, Image* ground)
	{
		COLORREF sidePosColor = ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y + yOffset));
		if (sidePosColor == WALLCOLOR) {
			while (sidePosColor == WALLCOLOR) {
				playerPos.x += direction;
				sidePosColor = ground->GetPixel(static_cast<int>(playerPos.x + xOffset), static_cast<int>(playerPos.y + yOffset));
				mPlayerRigidBody->SetVelocity(velocityChange);
			}
			mPlayerTR->SetPos(playerPos);
		}
	}



	void Pixel_Ground::Check_LoopStoneEnter_R()
	{
		Vector2 playerPos = mPlayerTR->GetPos();

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF colorcheck = selectedImage->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 50.f));

		if (colorcheck != STONEGREY_LOOPENTER)
			return;

		if (mRotationcheck == GROUNDCOLOR)
		{
			mPlayerRigidBody->SetGravity(Vector2{ 1500.0f,0.0f });
			mRotationcheck = mLOOPENTERCOLOR;
		}
	}
	void Pixel_Ground::Check_MidLoopStone_R()
	{
		if (mRotationcheck != mLOOPENTERCOLOR)
			return;

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;

		bool LoopStoneMeet = false;
		Vector2 playerPos = mPlayerTR->GetPos();
		COLORREF colorcheck;


		for (int i = 0; i < 5; ++i)
		{
			for (int j = -30; j < 1; ++j)
			{
				colorcheck = selectedImage->GetPixel(static_cast<int>(playerPos.x) + 40 + i, static_cast<int>(playerPos.y) + j);
				if (colorcheck == STONEORANGE_LOOPHALF)
				{
					LoopStoneMeet = true;

					mPlayerTR->SetPos(Vector2(playerPos.x + i, playerPos.y - j));
					break;
				}
			}
		}
		if (!LoopStoneMeet)
			return;
		else
		{
			static int count = 0;
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ -1500.0f,0.f });

			Vector2 curVelocity = mPlayerRigidBody->GetVelocity();
			mPlayerRigidBody->SetVelocity(Vector2(curVelocity.y * 0.25f, 0.f));

			mPlayerRigidBody->AddForce(Vector2{ -10000.f,1000.f });
			mRotationcheck = mLOOPAFTERHALF;
			count++;
			mCirclecheck = mCirclecheck * -1;
		}
	}
	void Pixel_Ground::Check_FinalLoopStone_R()
	{

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
	
		COLORREF colorcheck = selectedImage->GetPixel(static_cast<int>(mPlayerTR->GetPos().x) + 70, static_cast<int>(mPlayerTR->GetPos().y) + 20);
		if (colorcheck != STONERED_LOOPENTER)
			return;

		if (mRotationcheck == mLOOPAFTERHALF)
		{
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
			mRotationcheck = mGROUND;
		}
	}
	//if (mMap_Check == 1)
	//{
	//	COLORREF colorcheck = mCicle_Rturn2->GetPixel(static_cast<int>(mPlayerTR->GetPos().x) + 40, static_cast<int>(mPlayerTR->GetPos().y) + 40);
	//	if (colorcheck != STONERED_LOOPENTER)
	//		return;
	//	if (mRotationcheck == mLOOPAFTERHALF)
	//	{
	//		Vector2 TempVel;
	//		TempVel = mPlayerRigidBody->Getgravity();
	//		mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
	//		mRotationcheck = mGROUND;
	//	}
	//}

	void Pixel_Ground::CheckLoopStartColl_R()
	{
		if (mRotationcheck != mLOOPENTERCOLOR)
			return;

		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;

		if (mCircle_pice == 1)
		{
			Xrevice = 90.0f;
			Yrevice = 80.0f;
		}
		else if (mCircle_pice == 2)
		{
			Xrevice = 115.0f;
			Yrevice = 50.0f;
		}
		else if (mCircle_pice == 3)
		{
			Xrevice = 115.0f;
			Yrevice = 0.0f;
		}
		else if (mCircle_pice == 4)
		{
			Xrevice = 60.0f;
			Yrevice = -35.0f;
		}

		Vector2 playerPos = mPlayerTR->GetPos();

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));

		if (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
		{
			mPlayerRigidBody->SetGround(true);
			while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				playerPos.x -= 1;
				color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			}
			mPlayerTR->SetPos(playerPos);
		}
		else
		{
			mPlayerRigidBody->SetGround(false);
			int check = (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump) ? 2 : 10;
			COLORREF colorDown = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice + check), static_cast<int>(playerPos.y + Yrevice));

			if (colorDown == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				playerPos.x += check - 1;
				while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x -= 1;
					color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
		}
	}
	void Pixel_Ground::CheckLoopHalfColl_R()
	{
		//if (mRotationcheck != mLOOPAFTERHALF)
		//	return;

		Vector2 playerPos = mPlayerTR->GetPos();

		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;


		if (mCircle_pice == 4)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 5)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 6)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -180.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 7)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF rotation = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
		if (rotation == GROUNDBLUE_LOOPCOURSE_LEFT)
		{
			mPlayerRigidBody->SetGround(true);
			while (rotation == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				playerPos.x += 1;
				rotation = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			}
			mPlayerTR->SetPos(playerPos);
		}
		else
		{
			int check = 50;
			if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
				check = 2;
			COLORREF colorDown = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice - check), static_cast<int>(playerPos.y + Yrevice));
			if (colorDown == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				playerPos.x -= check - 1;
				COLORREF colorUp = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				while (colorUp == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x += 1;
					colorUp = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				mPlayerRigidBody->SetGround(false);
			}
		}	
	}


	void Pixel_Ground::Check_LoopStoneEnter_L()
	{
		Vector2 playerPos = mPlayerTR->GetPos();
		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF colorcheck = selectedImage->GetPixel(static_cast<int>(playerPos.x + 40), static_cast<int>(playerPos.y + 50));
		if (colorcheck != STONERED_LOOPENTER)
			return;

		if (mRotationcheck == GROUNDCOLOR)
		{
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ -1000.0f,0.0f });
			mRotationcheck = mLOOPAFTERHALF;
		}
		/*if (mMap_Check == 0)
		{
			COLORREF colorcheck = mCicle_Lturn->GetPixel(static_cast<int>(playerPos.x + 40), static_cast<int>(playerPos.y + 50));
			if (colorcheck != STONERED_LOOPENTER)
				return;

			if (mRotationcheck == GROUNDCOLOR)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ -1000.0f,0.0f });
				mRotationcheck = mLOOPAFTERHALF;
			}
		}
		if (mMap_Check == 1)
		{
			COLORREF colorcheck = mCicle_Lturn2->GetPixel(static_cast<int>(playerPos.x + 40), static_cast<int>(playerPos.y + 50));
			if (colorcheck != STONERED_LOOPENTER)
				return;

			if (mRotationcheck == GROUNDCOLOR)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ -1000.0f,0.0f });
				mRotationcheck = mLOOPAFTERHALF;
			}
		}*/
	}
	void Pixel_Ground::Check_MidLoopStone_L()
	{
		//if (mRotationcheck != mLOOPAFTERHALF)
		//	return;
		Vector2 playerPos = mPlayerTR->GetPos();
		COLORREF colorcheck;
		bool LoopStoneMeet = false;


		for (int i = 10; i > 0; --i)
		{
			for (int j = -20; j < 1; ++j)
			{
				Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
				colorcheck = selectedImage->GetPixel(static_cast<int>(playerPos.x + 60 + i), static_cast<int>(playerPos.y + j));
				if (colorcheck == STONEORANGE_LOOPHALF)
				{
					LoopStoneMeet = true;
					//DEBUG_PRINT("Sonic Orange Stone Meet Pos(%3d, %3d) : (%3.2f , %3.2f)\n", i, j, playerPos.x + i, playerPos.y + j);
					mPlayerTR->SetPos(Vector2(playerPos.x + i, playerPos.y - j));
					break;
				}			
			}
		}
		if (!LoopStoneMeet)
			return;
		else
		{
			static int count = 0;
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ 1000.0f,0.f });

			Vector2 curVelocity = mPlayerRigidBody->GetVelocity();
			mPlayerRigidBody->SetVelocity(Vector2(curVelocity.y * -0.25f, 0.f));

			mPlayerRigidBody->AddForce(Vector2{ 10000.f,1000.f });
			mRotationcheck = mLOOPENTERCOLOR;
			count++;
			//DEBUG_PRINT("Sonic Orange Stone Meet Count : %d\n", count);
			mCirclecheck = mCirclecheck * -1;
		}

	}
	void Pixel_Ground::Check_FinalLoopStone_L()
	{

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF colorcheck = selectedImage->GetPixel(static_cast<int>(mPlayerTR->GetPos().x), static_cast<int>(mPlayerTR->GetPos().y) + 100);
		if (colorcheck != STONEGREY_LOOPENTER)
			return;

		if (mRotationcheck == mLOOPENTERCOLOR)
		{
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
			mRotationcheck = mGROUND;
		}		
	}


	void Pixel_Ground::CheckLoopStartColl_L()
	{
		//if (mRotationcheck != mLOOPAFTERHALF)
		//	return;

		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;

		if (mCircle_pice == 0)
		{
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ 0.0f,500.0f });
			mRotationcheck = mGROUND;
			Pixel_Ground::CheckTerrian();
		}

		if (mCircle_pice == 7)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 6)
		{
			Xrevice = -10.0f;
			Yrevice = 80.0f;
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -180.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;

		}
		else if (mCircle_pice == 5)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 4)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}


		Vector2 playerPos = mPlayerTR->GetPos();

		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
		if (color1 == GROUNDBLUE_LOOPCOURSE_LEFT)
		{
			mPlayerRigidBody->SetGround(true);
			while (color1 == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				playerPos.x += 1;
				color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			}
			mPlayerTR->SetPos(playerPos);
		}
		else
		{
			int check = 50;
			if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
				check = 2;
			COLORREF colorDown = selectedImage->GetPixel(static_cast<int>(playerPos.x - check), static_cast<int>(playerPos.y));
			if (colorDown == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				playerPos.x -= check - 1;
				COLORREF colorUp = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				while (colorUp == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x += 1;
					colorUp = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				mPlayerRigidBody->SetGround(false);
			}
		}	
	}
	void Pixel_Ground::CheckLoopHalfColl_L()
	{
		//if (mRotationcheck != mLOOPENTERCOLOR)
		//	return;

		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;
		float Xrevice = 0.0f;
		float Yrevice = 0.0f;

		if (mCircle_pice == 0)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 1)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 45.f);
			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 2)
		{

			Vector2 rotation = { radius, 0.0f };

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 3)
		{

			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -45.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
		}
		else if (mCircle_pice == 4)
		{

			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -90.f);
			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y - 10.0f;
		}


		Vector2 playerPos = mPlayerTR->GetPos();
		Image* selectedImage = (mMap_Check == 0) ? mCicle_Rturn : mCicle_Rturn2;
		COLORREF color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
		if (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
		{
			mPlayerRigidBody->SetGround(true);
			while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				playerPos.x -= 1;
				color1 = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			}
			mPlayerTR->SetPos(playerPos);
		}
		else
		{
			int check = 50;
			if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
				check = 2;
			COLORREF colorDown = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice + check), static_cast<int>(playerPos.y + Yrevice));
			if (colorDown == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				playerPos.x += check - 1;
				COLORREF colorUp = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				while (colorUp == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x -= 1;
					colorUp = selectedImage->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				mPlayerRigidBody->SetGround(false);
			}
		}
	}

}