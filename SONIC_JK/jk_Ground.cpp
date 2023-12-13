#include "jk_Ground.h"

#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"

#include "jk_Input.h"
#include "jk_Camera.h"

#include "jk_SONIC.h"
#include "jk_Tails.h"

// 땅, 원 진입(300도 ~ 89도), 원의 중간 이후(90도 ~ 약240도) 
//#define GROUND			0
//#define LOOPENTERCOLOR	1
//#define LOOPAFTERHALF		2

#define GROUNDCOLOR						RGB(0, 0, 0)
#define WALLCOLOR						RGB(0, 12, 123)
#define FLYLCOLOR						RGB(51, 102, 102)

#define STONEGREY_LOOPENTER				RGB(127, 127, 127) 
#define STONEORANGE_LOOPHALF			RGB(255, 127, 0)
#define STONERED_LOOPENTER				RGB(255, 0, 0)

#define GROUNDYELLO_LOOPCOURSE_RIGHT	RGB(255, 255, 0)
#define GROUNDBLUE_LOOPCOURSE_LEFT		RGB(0, 0, 255)


namespace jk
{
	Vector2 Circle1_Top = Vector2{ 20229.f,3127.f };
	float Radian_Cicle1 = 0.0f;
	float Degree_Cicle1 = 0.0f;


	float Radian_Circle1_Tails = 0.0f;
	float Degree_Circle1_Tails = 0.0f;

	Ground::Ground()
		: mPlayer(nullptr)
		, mPlayer2(nullptr)
		, mPlayerTR(nullptr)
		, mPlayer_Tails_TR(nullptr)
		, mPlayerRigidBody(nullptr)
		, mRigidbody_Tails(nullptr)
		, SonicDir(0)
		, TailsDir(0)

		, GROUND(0)
		, LOOPENTERCOLOR(1)
		, LOOPAFTERHALF(2)

		, Circlecheck(1)
		//act1-1
		, Ground_Image(nullptr)
		, Cicle_Rturn(nullptr)
		, Cicle_Lturn(nullptr)
		//act1-2
		, Ground_Image2(nullptr)
		, Cicle_Rturn2(nullptr)
		, Cicle_Lturn2(nullptr)
		//act1-3
		, Ground_Image3(nullptr)
		//act6
		, Ground_Image4(nullptr)

		, mDirect(1)
		, Circle_pice(0)
		, mRotationcheck(0)

		, Circle1_Center(0.f, 0.f)
		, Circle1_Center2(0.f, 0.f)

		, WallCheck(0)
		, LoopStoneMeet(false)
		, map_chek(0)
		, mCollider(nullptr)

	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		Ground_Image = Resources::Load<Image>(L"Ground_Image", L"..\\Resources\\Ground_Image.bmp");
		Cicle_Rturn = Resources::Load<Image>(L"Cicle_Rturn", L"..\\Resources\\Cicle_Rturn.bmp");
		Cicle_Lturn = Resources::Load<Image>(L"Cicle_Lturn", L"..\\Resources\\Cicle_Lturn.bmp");
		Circle1_Center = Vector2{ 20229.f,3406.f };
		Circle1_Center2 = Vector2{ 9195.f, 3705.f };

		Ground_Image2 = Resources::Load<Image>(L"Ground_Image2", L"..\\Resources\\Ground_Act1_2.bmp");
		Cicle_Rturn2 = Resources::Load<Image>(L"Cicle_Rturn2", L"..\\Resources\\ActBG_1_2\\Cicle_Rturn2.bmp");
		Cicle_Lturn2 = Resources::Load<Image>(L"Cicle_Lturn2", L"..\\Resources\\ActBG_1_2\\Cicle_Lturn2.bmp");

		Ground_Image3 = Resources::Load<Image>(L"Ground_Image3", L"..\\Resources\\ActBG_1_3\\Ground_Act1_3.bmp");
		Ground_Image4 = Resources::Load<Image>(L"Ground_Image4", L"..\\Resources\\ActBG_6\\act 6-boss_ground.bmp");

		Gameobject::Initialize();
	}

	void Ground::Update()
	{

		mPlayerTR = mPlayer->GetComponent<Transform>();
		//mPlayer_Tails_TR = mPlayer2->GetComponent<Transform>();

		Vector2 Player_Position = mPlayerTR->GetPos();
		//Vector2 Player_Tails_Poistion = mPlayer_Tails_TR->GetPos();

		SonicDir = mPlayer->GetSonicDir();
		//TailsDir = mPlayer2->GetTailsDir();


	
		#pragma region 소닉회전각
		Radian_Cicle1 = atan2(Circle1_Center.y - mPlayerTR->GetPos().y, Circle1_Center.x - mPlayerTR->GetPos().x);
		Degree_Cicle1 = Radian_Cicle1 * (180.f / static_cast<float>(PI));
		if (Degree_Cicle1 <= -67.5f && Degree_Cicle1 > -112.5f)//중앙하부 
		{
			Circle_pice = 0;
		}

		if (Degree_Cicle1 <= -112.5f && Degree_Cicle1 > -157.5f)//오른쪽하부 
		{
			Circle_pice = 1;
		}

		if (Degree_Cicle1 <= -157.5f || (Degree_Cicle1 >= 157.5f && Degree_Cicle1 <= 180.f))// 오른쪽옆
		{
			Circle_pice = 2;
		}

		if (Degree_Cicle1 >= 112.5f && Degree_Cicle1 < 157.5f)// 오른쪽상부
		{
			Circle_pice = 3;
		}

		if (Degree_Cicle1 >= 67.5f && Degree_Cicle1 < 112.5f)// 중앙상부
		{
			Circle_pice = 4;
		}

		if (Degree_Cicle1 >= 22.5f && Degree_Cicle1 < 67.5f)// 왼쪽상부
		{
			Circle_pice = 5;
		}

		if ((Degree_Cicle1 <= 0.f && Degree_Cicle1 > -22.5f) || (Degree_Cicle1 >= 0.f && Degree_Cicle1 < 22.5f))// 왼쪽옆
		{
			Circle_pice = 6;
		}

		if (Degree_Cicle1 <= -22.5f && Degree_Cicle1 > -67.5f)//왼쪽하부 
		{
			Circle_pice = 7;
		}
		#pragma endregion

		

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


		//소닉 Circle 진입확인
		Vector2 playerPos = mPlayerTR->GetPos();
		if (map_chek == 0)
		{
			COLORREF color_Right = static_cast<int>(Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + 100.f), static_cast<int>(playerPos.y + 50.f)));
			if (mRotationcheck == GROUNDCOLOR && color_Right == GROUNDBLUE_LOOPCOURSE_LEFT) 
			{
				mDirect = 1;
			}
			COLORREF  color_Left = static_cast<int>(Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y + 50.f)));
			if (mRotationcheck == GROUNDCOLOR && color_Left == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				mDirect = -1;
			}
		}
		if (map_chek == 1)
		{
			COLORREF color_Right = static_cast<int>(Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + 100.f), static_cast<int>(playerPos.y + 50.f)));
			if (mRotationcheck == GROUNDCOLOR && color_Right == GROUNDBLUE_LOOPCOURSE_LEFT) // Input::GetKey(eKeyCode::RIGHT) &&
			{
				mDirect = 1;
			}
			COLORREF  color_Left = static_cast<int>(Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y + 50.f)));
			if (mRotationcheck == GROUNDCOLOR && color_Left == GROUNDYELLO_LOOPCOURSE_RIGHT)// && Input::GetKey(eKeyCode::LEFT)
			{
				mDirect = -1;
			}
		}

		CheckGround();

		if (mDirect == 1)
		{
			if (Circlecheck == 1)
			{
				CheckLoopStoneEnter_R();
			}

			if (mRotationcheck == LOOPENTERCOLOR)
			{
				CheckLoopEnter_R();
			}
			if (mRotationcheck == LOOPENTERCOLOR)
			{
				CheckLoopStoneSecond_R();
			}
			if (mRotationcheck == LOOPAFTERHALF)
			{
				CheckLoopHalfAfter_R();
			}

			if (Circlecheck == -1)
			{
				CheckLoopStoneGround_R();
			}
		}

		else if (mDirect == -1)
		{
			if (Circlecheck == -1)
			{
				CheckLoopStoneEnter_L();
			}

			CheckLoopHalfAfter_L();
			CheckLoopStoneSecond_L();
			CheckLoopEnter_L();
			if (Circlecheck == 1)
			{
				CheckLoopStoneGround_L();
			}
		}

		Gameobject::Update();
	}

	void Ground::Render(HDC hdc)
	{
		Gameobject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 mpos = pos - (Camera::CaluatePos(pos) - pos);

		if (map_chek == 0)
		{
			if (Input::GetKey(eKeyCode::Q))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, Ground_Image->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
			if (Input::GetKey(eKeyCode::W))
			{
				TransparentBlt(hdc, 0, 0, 1200, 840, Cicle_Rturn->GetHdc(),
					static_cast<int>(mpos.x), static_cast<int>(mpos.y), 1200, 840, RGB(255, 255, 255));
			}
		}

		if (map_chek == 1)
		{
			//TransparentBlt(hdc, 0, 0, 1200, 840, Ground_Image2->GetHdc(), mpos.x, mpos.y, 1200, 840, RGB(255, 255, 255));
		}

		if (map_chek == 2)
		{
			//TransparentBlt(hdc, 0, 0, 1200, 840, Ground_Image3->GetHdc(), mpos.x, mpos.y, 1200, 840, RGB(255, 255, 255));
		}

		if (map_chek == 3)
		{
			//TransparentBlt(hdc, 0, 0, 1200, 840, Ground_Image4->GetHdc(), mpos.x, mpos.y, 1200, 840, RGB(255, 255, 255));
		}
	}

	void Ground::Realease()
	{
		Gameobject::Release();
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
	}

	Image* Ground::GetGroundImage()
	{		
		if (!Ground_Image)
			return nullptr;

		return Ground_Image;		
	}

	Image* Ground::GetGroundImage2()
	{
		if (!Ground_Image2)
			return nullptr;

		return Ground_Image2;
	}

	Image* Ground::GetGroundImage3()
	{
		if (!Ground_Image3)
			return nullptr;

		return Ground_Image3;
	}

	Image* Ground::GetGroundImage4()
	{
		if (!Ground_Image4)
			return nullptr;

		return Ground_Image4;
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


	void Ground::CheckGround()
	{
		if (mRotationcheck != GROUND)
			return;

		Vector2 playerPos = mPlayerTR->GetPos();
		Vector2 playerPos_Tails = mPlayer_Tails_TR->GetPos();


		////////////소닉 발판 Act1-1//////////
		if (map_chek == 0)
		{
			float Xrevice = 40.0f;
			float Yrevice = 100.0f;
			COLORREF playerFootPosColor = Ground_Image->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (playerFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				mPlayerRigidBody->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{

				//mPlayerRigidBody->SetGround(false);
				int check = 20;

				if ((mPlayer->Getsonicstate() == Sonic::eSonicState::Jump) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Hurt) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Spring_Jump))
				{
					check = 2;
				}

				COLORREF colorDown = Ground_Image->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice + check));
				if (colorDown == GROUNDCOLOR)
				{
					playerPos.y += check - 1;
					COLORREF colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}

			//소닉 그라운드벽면		
			float Xrevice_side = 0.0f;
			float Yrevice_side = 50.0f;
			//오른쪽벽 	WallCheck가 1일땐 오른쪽으로 미는 모션, -1일떈 왼쪽으로 미는 모션, 0일땐 그냥 아이들상태(소닉에서 설정필요)
			COLORREF player_R_Side_PosColor = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_R_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Right = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Right == WALLCOLOR)
				{
					while (color_Push_Right == WALLCOLOR)
					{
						playerPos.x -= 1;
						color_Push_Right = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });

					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}


			//왼쪽벽
			COLORREF player_L_Side_PosColor = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_L_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Left = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
				mPlayerRigidBody->SetGround(true);
				if (color_Push_Left == WALLCOLOR)
				{
					while (color_Push_Left == WALLCOLOR)
					{
						playerPos.x += 1;
						color_Push_Left = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}

			//위쪽면
			COLORREF player_UP_Side_PosColor = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
			if (player_UP_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_DOWN = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
				if (color_Push_DOWN == WALLCOLOR)
				{
					while (color_Push_DOWN == WALLCOLOR)
					{
						playerPos.y += 1;
						color_Push_DOWN = Ground_Image->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ mPlayerRigidBody->GetVelocity().x,0.f });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}

			//FLY통
			COLORREF player_Down_Side_PosColor = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 100.f));
			if (player_Down_Side_PosColor == FLYLCOLOR)
			{
				COLORREF color_Push_DOWN = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 100.f));
				mPlayerRigidBody->SetGround(true);
				if (color_Push_DOWN == FLYLCOLOR)
				{
					while (color_Push_DOWN == FLYLCOLOR)
					{
						playerPos.y -= 1;
						color_Push_DOWN = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 100.f));
						WallCheck = 1;
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}
		}

		////////////소닉 발판 Act1-2//////////
		if (map_chek == 1)
		{
			/////////소닉 발판 Act1-2////////////
			float Xrevice = 40.0f;
			float Yrevice = 100.0f;
			COLORREF playerFootPosColor = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (playerFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				mPlayerRigidBody->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}

					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				int check = 30;

				if ((mPlayer->Getsonicstate() == Sonic::eSonicState::Jump) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Hurt) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Spring_Jump))
				{
					check = 2;
				}


				COLORREF colorDown = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice + check));
				if (colorDown == GROUNDCOLOR)
				{
					playerPos.y += check - 1;
					COLORREF colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}

			//소닉 그라운드벽면		
			float Xrevice_side = 0.0f;
			float Yrevice_side = 50.0f;

			//오른쪽벽 	WallCheck가 1일땐 오른쪽으로 미는 모션, -1일떈 왼쪽으로 미는 모션, 0일땐 그냥 아이들상태(소닉에서 설정필요)
			COLORREF player_R_Side_PosColor = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_R_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Right = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Right == WALLCOLOR)
				{
					while (color_Push_Right == WALLCOLOR)
					{
						playerPos.x -= 1;
						color_Push_Right = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}

			//왼쪽벽
			COLORREF player_L_Side_PosColor = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_L_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Left = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));

				if (color_Push_Left == WALLCOLOR)
				{
					while (color_Push_Left == WALLCOLOR)
					{
						playerPos.x += 1;
						color_Push_Left = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}


			//위쪽면
			COLORREF player_UP_Side_PosColor = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
			if (player_UP_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_DOWN = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
				mPlayerRigidBody->SetGround(true);
				if (color_Push_DOWN == WALLCOLOR)
				{
					while (color_Push_DOWN == WALLCOLOR)
					{
						playerPos.y += 1;
						color_Push_DOWN = Ground_Image2->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
						WallCheck = 1;
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}
		}

		////////////소닉 발판 Act1-3//////////
		if (map_chek == 2)
		{

			float Xrevice = 40.0f;
			float Yrevice = 100.0f;
			COLORREF playerFootPosColor = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (playerFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				mPlayerRigidBody->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}

					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				int check = 30;

				if ((mPlayer->Getsonicstate() == Sonic::eSonicState::Jump) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Hurt) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Spring_Jump))
				{
					check = 2;
				}


				COLORREF colorDown = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice + check));
				if (colorDown == GROUNDCOLOR)
				{
					playerPos.y += check - 1;
					COLORREF colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}

			//소닉 그라운드벽면		
			float Xrevice_side = 0.0f;
			float Yrevice_side = 120.0f;

			//오른쪽벽 	WallCheck가 1일땐 오른쪽으로 미는 모션, -1일떈 왼쪽으로 미는 모션, 0일땐 그냥 아이들상태(소닉에서 설정필요)
			COLORREF player_R_Side_PosColor = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_R_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Right = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Right == WALLCOLOR)
				{
					while (color_Push_Right == WALLCOLOR)
					{
						playerPos.x -= 1;
						color_Push_Right = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}

			//왼쪽벽
			COLORREF player_L_Side_PosColor = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_L_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Left = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Left == WALLCOLOR)
				{
					while (color_Push_Left == WALLCOLOR)
					{
						playerPos.x += 1;
						playerPos.y += 1;
						color_Push_Left = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}


			//위쪽면
			COLORREF player_UP_Side_PosColor = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
			if (player_UP_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_DOWN = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
				mPlayerRigidBody->SetGround(true);
				if (color_Push_DOWN == WALLCOLOR)
				{
					while (color_Push_DOWN == WALLCOLOR)
					{
						playerPos.y += 1;
						color_Push_DOWN = Ground_Image3->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
						WallCheck = 1;
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}
		}

		////////////소닉 발판 Act6//////////
		if (map_chek == 3)
		{

			float Xrevice = 40.0f;
			float Yrevice = 100.0f;
			COLORREF playerFootPosColor = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (playerFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				mPlayerRigidBody->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}

					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				int check = 30;

				if ((mPlayer->Getsonicstate() == Sonic::eSonicState::Jump) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Hurt) || (mPlayer->Getsonicstate() == Sonic::eSonicState::Spring_Jump))
				{
					check = 2;
				}


				COLORREF colorDown = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice + check));
				if (colorDown == GROUNDCOLOR)
				{
					playerPos.y += check - 1;
					COLORREF colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDCOLOR)
					{
						playerPos.y -= 1;
						colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}

			//소닉 그라운드벽면		
			float Xrevice_side = 0.0f;
			float Yrevice_side = 50.0f;

			//오른쪽벽 	WallCheck가 1일땐 오른쪽으로 미는 모션, -1일떈 왼쪽으로 미는 모션, 0일땐 그냥 아이들상태(소닉에서 설정필요)
			COLORREF player_R_Side_PosColor = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_R_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Right = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Right == WALLCOLOR)
				{
					while (color_Push_Right == WALLCOLOR)
					{
						playerPos.x -= 1;
						color_Push_Right = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 80.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}

			//왼쪽벽
			COLORREF player_L_Side_PosColor = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
			if (player_L_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_Left = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
				if (color_Push_Left == WALLCOLOR)
				{
					while (color_Push_Left == WALLCOLOR)
					{
						playerPos.x += 1;
						color_Push_Left = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 0.f), static_cast<int>(playerPos.y + Yrevice_side));
						WallCheck = 1;
						mPlayerRigidBody->SetVelocity(Vector2{ 0.f,mPlayerRigidBody->GetVelocity().y });
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}


			//위쪽면
			COLORREF player_UP_Side_PosColor = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
			if (player_UP_Side_PosColor == WALLCOLOR)
			{
				COLORREF color_Push_DOWN = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
				mPlayerRigidBody->SetGround(true);
				if (color_Push_DOWN == WALLCOLOR)
				{
					while (color_Push_DOWN == WALLCOLOR)
					{
						playerPos.y += 1;
						color_Push_DOWN = Ground_Image4->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y - 20.f));
						WallCheck = 1;
					}
					mPlayerTR->SetPos(playerPos);
				}
			}
			else
			{
				WallCheck = 0;
			}
		}
	

		///////테일즈 발판 act1-1//////////
		if (map_chek == 0)
		{
			COLORREF tailsFootPosColor = Ground_Image->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f) + 1);
			if (tailsFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
				mRigidbody_Tails->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}

			}
			else
			{
				int check = 30;
				if ((mPlayer2->GetTails_state() == Tails::eTailsState::Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Movejump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Spring_Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Hurt))
				{
					//mRigidbody_Tails->SetVelocity(Vector2{ 0.0f,-450.f });
					check = 2;
				}
				COLORREF colorDown = Ground_Image->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100 + check);
				if (colorDown == RGB(0, 0, 0))
				{
					playerPos_Tails.y += check - 1;
					COLORREF colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					while (colorUp == RGB(0, 0, 0))
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}
				else
				{
					mRigidbody_Tails->SetGround(false);
				}
			}
		}

		///////테일즈 발판 act1-2//////////
		if (map_chek == 1)
		{
			COLORREF tailsFootPosColor = Ground_Image2->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f) + 1);
			if (tailsFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
				mRigidbody_Tails->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}

			}
			else
			{
				int check = 30;
				if ((mPlayer2->GetTails_state() == Tails::eTailsState::Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Movejump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Spring_Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Hurt))
				{
					//mRigidbody_Tails->SetVelocity(Vector2{ 0.0f,-450.f });
					check = 2;
				}
				COLORREF colorDown = Ground_Image2->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100 + check);
				if (colorDown == RGB(0, 0, 0))
				{
					playerPos_Tails.y += check - 1;
					COLORREF colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					while (colorUp == RGB(0, 0, 0))
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image2->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}
				else
				{
					mRigidbody_Tails->SetGround(false);
				}
			}
		}

		///////테일즈 발판 act1-3//////////
		if (map_chek == 2)
		{
			COLORREF tailsFootPosColor = Ground_Image3->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f) + 1);
			if (tailsFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
				mRigidbody_Tails->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}

			}
			else
			{
				int check = 30;
				if ((mPlayer2->GetTails_state() == Tails::eTailsState::Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Movejump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Spring_Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Hurt))
				{
					//mRigidbody_Tails->SetVelocity(Vector2{ 0.0f,-450.f });
					check = 2;
				}
				COLORREF colorDown = Ground_Image3->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100 + check);
				if (colorDown == RGB(0, 0, 0))
				{
					playerPos_Tails.y += check - 1;
					COLORREF colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					while (colorUp == RGB(0, 0, 0))
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image3->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}
				else
				{
					mRigidbody_Tails->SetGround(false);
				}
			}
		}

		///////테일즈 발판 act6//////////
		if (map_chek == 3)
		{
			COLORREF tailsFootPosColor = Ground_Image4->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f) + 1);
			if (tailsFootPosColor == GROUNDCOLOR)
			{
				COLORREF colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
				mRigidbody_Tails->SetGround(true);
				if (colorUp == GROUNDCOLOR)
				{
					while (colorUp == GROUNDCOLOR)
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos_Tails.x + 75.f), static_cast<int>(playerPos_Tails.y + 100.f));
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}

			}
			else
			{
				int check = 30;
				if ((mPlayer2->GetTails_state() == Tails::eTailsState::Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Movejump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Spring_Jump) || (mPlayer2->GetTails_state() == Tails::eTailsState::Hurt))
				{
					//mRigidbody_Tails->SetVelocity(Vector2{ 0.0f,-450.f });
					check = 2;
				}
				COLORREF colorDown = Ground_Image4->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100 + check);
				if (colorDown == RGB(0, 0, 0))
				{
					playerPos_Tails.y += check - 1;
					COLORREF colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					while (colorUp == RGB(0, 0, 0))
					{
						playerPos_Tails.y -= 1;
						colorUp = Ground_Image4->GetPixel(static_cast<int>(playerPos_Tails.x), static_cast<int>(playerPos_Tails.y) + 100);
					}
					mPlayer_Tails_TR->SetPos(playerPos_Tails);
				}
				else
				{
					mRigidbody_Tails->SetGround(false);
				}
			}
		}
	}

	void Ground::CheckLoopStoneEnter_R()
	{
		Vector2 playerPos = mPlayerTR->GetPos();
		COLORREF colorcheck = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 50.f));
		if (map_chek == 0)
		{
			colorcheck = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 50.f));
		}
		else if (map_chek == 1)
		{
			colorcheck = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + 40.f), static_cast<int>(playerPos.y + 50.f));
		}

		if (colorcheck != STONEGREY_LOOPENTER)
			return;

		if (mRotationcheck == GROUNDCOLOR)
		{
			mPlayerRigidBody->SetGravity(Vector2{ 1500.0f,0.0f });
			mRotationcheck = LOOPENTERCOLOR;
		}
	}

	void Ground::CheckLoopEnter_R()
	{
		if (mRotationcheck != LOOPENTERCOLOR)
			return;

		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;

		if (Circle_pice == 0)
		{
			//Vector2 TempVel;
			//TempVel = mPlayerRigidBody->Getgravity();	
		}
		if (Circle_pice == 1)
		{
			Xrevice = 90.0f;
			Yrevice = 80.0f;
		}
		else if (Circle_pice == 2)
		{

			Xrevice = 115.0f;
			Yrevice = 50.0f;
		}
		else if (Circle_pice == 3)
		{
			Xrevice = 115.0f;
			Yrevice = 0.0f;
		}
		else if (Circle_pice == 4)
		{
			Xrevice = 60.0f;
			Yrevice = -35.0f;
		}

		Vector2 playerPos = mPlayerTR->GetPos();
		if (map_chek == 0)
		{
			COLORREF color1 = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				mPlayerRigidBody->SetGround(true);
				while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x -= 1;
					color1 = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				int check = 10;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice + check), static_cast<int>(playerPos.y + Yrevice));
				if (colorDown == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x += check - 1;
					COLORREF colorUp = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDYELLO_LOOPCOURSE_RIGHT)
					{
						playerPos.x -= 1;
						colorUp = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}
		}

		else if (map_chek == 1)
		{
			COLORREF color1 = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				mPlayerRigidBody->SetGround(true);
				while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x -= 1;
					color1 = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				int check = 10;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice + check), static_cast<int>(playerPos.y + Yrevice));
				if (colorDown == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x += check - 1;
					COLORREF colorUp = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDYELLO_LOOPCOURSE_RIGHT)
					{
						playerPos.x -= 1;
						colorUp = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
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

	void Ground::CheckLoopStoneSecond_R()
	{
		if (map_chek == 0)
		{
			if (mRotationcheck != LOOPENTERCOLOR)
				return;

			bool LoopStoneMeet = false;
			Vector2 playerPos = mPlayerTR->GetPos();
			COLORREF colorcheck;


			for (int i = 0; i < 5; ++i)
			{
				for (int j = -30; j < 1; ++j)
				{
					colorcheck = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x) + 40 + i, static_cast<int>(playerPos.y) + j);
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
				mRotationcheck = LOOPAFTERHALF;
				count++;				
				Circlecheck = Circlecheck * -1;
			}
		}


		else if (map_chek == 1)
		{
			bool LoopStoneMeet = false;
			Vector2 playerPos = mPlayerTR->GetPos();
			COLORREF colorcheck;


			for (int i = 0; i < 5; ++i)
			{
				for (int j = -30; j < 1; ++j)
				{
					colorcheck = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x) + 40 + i, static_cast<int>(playerPos.y) + j);
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
				mPlayerRigidBody->SetGravity(Vector2{ -1500.0f,0.f });

				Vector2 curVelocity = mPlayerRigidBody->GetVelocity();
				mPlayerRigidBody->SetVelocity(Vector2(curVelocity.y * 0.25f, 0.f));
				//mPlayerRigidBody->SetVelocity(Vector2{fabs(TempVel.y) * -1 , fabs(TempVel.y)*1.0f });
				mPlayerRigidBody->AddForce(Vector2{ -10000.f,1000.f });
				mRotationcheck = LOOPAFTERHALF;
				count++;
				//DEBUG_PRINT("Sonic Orange Stone Meet Count : %d\n", count);
				Circlecheck = Circlecheck * -1;
			}
		}



	}

	void Ground::CheckLoopHalfAfter_R()
	{
		//if (mRotationcheck != LOOPAFTERHALF)
		//	return;

		Vector2 playerPos = mPlayerTR->GetPos();

		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;


		if (Circle_pice == 4)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 60.0f;
			//Yrevice = -35.0f;
		}
		else if (Circle_pice == 5)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 0.0f;
			//Yrevice = 0.0f;
		}
		else if (Circle_pice == 6)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -180.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = -10.0f;
			//Yrevice = 80.0f;
		}
		else if (Circle_pice == 7)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 0.0f;
			//Yrevice = 80.0f;
		}

		if (map_chek == 0)
		{
			COLORREF rotation = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y));
			rotation = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (rotation == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				mPlayerRigidBody->SetGround(true);
				while (rotation == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x += 1;
					rotation = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				int check = 50;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice - check), static_cast<int>(playerPos.y + Yrevice));
				if (colorDown == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x -= check - 1;
					COLORREF colorUp = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDBLUE_LOOPCOURSE_LEFT)
					{
						playerPos.x += 1;
						colorUp = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}
		}
		else if (map_chek == 1)
		{
			COLORREF rotation = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x), static_cast<int>(playerPos.y));
			rotation = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
			if (rotation == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				mPlayerRigidBody->SetGround(true);
				while (rotation == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x += 1;
					rotation = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				int check = 50;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice - check), static_cast<int>(playerPos.y + Yrevice));
				if (colorDown == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x -= check - 1;
					COLORREF colorUp = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDBLUE_LOOPCOURSE_LEFT)
					{
						playerPos.x += 1;
						colorUp = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
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

	void Ground::CheckLoopStoneGround_R()
	{
		//COLORREF colorcheck = Cicle_Lturn->GetPixel(mPlayerTR->GetPos().x , mPlayerTR->GetPos().y +50);

		if (map_chek == 0)
		{
			COLORREF colorcheck = Cicle_Lturn->GetPixel(static_cast<int>(mPlayerTR->GetPos().x) + 70, static_cast<int>(mPlayerTR->GetPos().y) + 20);
			if (colorcheck != STONERED_LOOPENTER)
				return;

			if (mRotationcheck == LOOPAFTERHALF)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
				mRotationcheck = GROUND;
			}
		}
		if (map_chek == 1)
		{
			COLORREF colorcheck = Cicle_Rturn2->GetPixel(static_cast<int>(mPlayerTR->GetPos().x) + 40, static_cast<int>(mPlayerTR->GetPos().y) + 40);
			if (colorcheck != STONERED_LOOPENTER)
				return;

			if (mRotationcheck == LOOPAFTERHALF)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
				mRotationcheck = GROUND;
			}
		}

	}

	void Ground::CheckLoopStoneEnter_L()
	{
		Vector2 playerPos = mPlayerTR->GetPos();


		if (map_chek == 0)
		{
			COLORREF colorcheck = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + 40), static_cast<int>(playerPos.y + 50));
			if (colorcheck != STONERED_LOOPENTER)
				return;

			if (mRotationcheck == GROUNDCOLOR)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ -1000.0f,0.0f });
				mRotationcheck = LOOPAFTERHALF;
			}
		}
		if (map_chek == 1)
		{
			COLORREF colorcheck = Cicle_Lturn2->GetPixel(static_cast<int>(playerPos.x + 40), static_cast<int>(playerPos.y + 50));
			if (colorcheck != STONERED_LOOPENTER)
				return;

			if (mRotationcheck == GROUNDCOLOR)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ -1000.0f,0.0f });
				mRotationcheck = LOOPAFTERHALF;
			}
		}
	}

	void Ground::CheckLoopEnter_L()
	{
		if (mRotationcheck != LOOPAFTERHALF)
			return;

		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;

		if (Circle_pice == 0)
		{
			Vector2 TempVel;
			TempVel = mPlayerRigidBody->Getgravity();
			mPlayerRigidBody->SetGravity(Vector2{ 0.0f,500.0f });
			mRotationcheck = GROUND;
			Ground::CheckGround();
		}

		if (Circle_pice == 7)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 0.0f;
			//Yrevice = 80.0f;
		}
		else if (Circle_pice == 6)
		{
			Xrevice = -10.0f;
			Yrevice = 80.0f;
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -180.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;

		}
		else if (Circle_pice == 5)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -135.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 0.0f;
			//Yrevice = 0.0f;
		}
		else if (Circle_pice == 4)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 60.0f;
			//Yrevice = -35.0f;
		}


		Vector2 playerPos = mPlayerTR->GetPos();

		if (map_chek == 0)
		{
			COLORREF color1 = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));

			if (color1 == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				mPlayerRigidBody->SetGround(true);
				while (color1 == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x += 1;
					color1 = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{

				int check = 50;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x - check), static_cast<int>(playerPos.y));
				if (colorDown == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x -= check - 1;
					COLORREF colorUp = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDBLUE_LOOPCOURSE_LEFT)
					{
						playerPos.x += 1;
						colorUp = Cicle_Lturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}
		}
		else if (map_chek == 1)
		{
			COLORREF color1 = Cicle_Lturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));

			if (color1 == GROUNDBLUE_LOOPCOURSE_LEFT)
			{
				mPlayerRigidBody->SetGround(true);
				while (color1 == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x += 1;
					color1 = Cicle_Lturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{

				int check = 50;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Lturn2->GetPixel(static_cast<int>(playerPos.x - check), static_cast<int>(playerPos.y));
				if (colorDown == GROUNDBLUE_LOOPCOURSE_LEFT)
				{
					playerPos.x -= check - 1;
					COLORREF colorUp = Cicle_Lturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDBLUE_LOOPCOURSE_LEFT)
					{
						playerPos.x += 1;
						colorUp = Cicle_Lturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
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

	void Ground::CheckLoopStoneSecond_L()
	{

		if (mRotationcheck != LOOPAFTERHALF)
			return;
		Vector2 playerPos = mPlayerTR->GetPos();
		COLORREF colorcheck;
		bool LoopStoneMeet = false;


		for (int i = 10; i > 0; --i)
		{
			for (int j = -20; j < 1; ++j)
			{
				if (map_chek == 0)
				{
					colorcheck = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + 60 + i), static_cast<int>(playerPos.y + j));
					if (colorcheck == STONEORANGE_LOOPHALF)
					{
						LoopStoneMeet = true;
						//DEBUG_PRINT("Sonic Orange Stone Meet Pos(%3d, %3d) : (%3.2f , %3.2f)\n", i, j, playerPos.x + i, playerPos.y + j);
						mPlayerTR->SetPos(Vector2(playerPos.x + i, playerPos.y - j));
						break;
					}
				}
				if (map_chek == 1)
				{
					colorcheck = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + 60 + i), static_cast<int>(playerPos.y + j));
					if (colorcheck == STONEORANGE_LOOPHALF)
					{
						LoopStoneMeet = true;
						//DEBUG_PRINT("Sonic Orange Stone Meet Pos(%3d, %3d) : (%3.2f , %3.2f)\n", i, j, playerPos.x + i, playerPos.y + j);
						mPlayerTR->SetPos(Vector2(playerPos.x + i, playerPos.y - j));
						break;
					}
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

			//mPlayerRigidBody->SetVelocity(Vector2{ fabs(TempVel.y),fabs(TempVel.y) }); 
			mPlayerRigidBody->AddForce(Vector2{ 10000.f,1000.f });
			mRotationcheck = LOOPENTERCOLOR;
			count++;
			//DEBUG_PRINT("Sonic Orange Stone Meet Count : %d\n", count);
			Circlecheck = Circlecheck * -1;
		}

	}

	void Ground::CheckLoopHalfAfter_L()
	{
		if (mRotationcheck != LOOPENTERCOLOR)
			return;

		Vector2 center = { 50.0f, 35.0f };
		float radius = 65.0f;
		float Xrevice = 0.0f;
		float Yrevice = 0.0f;
		/*if (Circle_pice == 0)
		{
			Xrevice = 75.f;
			Yrevice = 50.0f;
		}

		else if (Circle_pice == 1)
		{
			Xrevice = 90.0f;
			Yrevice = 80.0f;
		}
		else if (Circle_pice == 2)
		{
			Xrevice = 115.0f;
			Yrevice = 50.0f;
		}
		else if (Circle_pice == 3)
		{
			Xrevice = 115.0f;
			Yrevice = 0.0f;
		}
		else if (Circle_pice == 4)
		{
			Xrevice = 35.0f;
			Yrevice = -30.0f;
		}*/
		if (Circle_pice == 0)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 75.f;
			//Yrevice = 50.0f;
		}
		else if (Circle_pice == 1)
		{
			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, 45.f);
			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 90.0f;
			//Yrevice = 80.0f;
		}
		else if (Circle_pice == 2)
		{

			Vector2 rotation = { radius, 0.0f };

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 115.0f;
			//Yrevice = 50.0f;
		}
		else if (Circle_pice == 3)
		{

			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -45.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y;
			//Xrevice = 115.0f;
			//Yrevice = 0.0f;
		}
		else if (Circle_pice == 4)
		{

			Vector2 rotation = { radius, 0.0f };
			rotation = math::Rotate(rotation, -90.f);

			Xrevice = center.x + rotation.x;
			Yrevice = center.y + rotation.y - 10.0f;
			//Xrevice = 60.0f;
			//Yrevice = -35.0f;
		}


		Vector2 playerPos = mPlayerTR->GetPos();

		if (map_chek == 0)
		{
			COLORREF color1 = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));

			if (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				mPlayerRigidBody->SetGround(true);
				while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x -= 1;
					color1 = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				int check = 50;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice + check), static_cast<int>(playerPos.y + Yrevice));
				if (colorDown == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x += check - 1;
					COLORREF colorUp = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDYELLO_LOOPCOURSE_RIGHT)
					{
						playerPos.x -= 1;
						colorUp = Cicle_Rturn->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					}
					mPlayerTR->SetPos(playerPos);
				}
				else
				{
					mPlayerRigidBody->SetGround(false);
				}
			}
		}
		if (map_chek == 1)
		{
			COLORREF color1 = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));

			if (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
			{
				mPlayerRigidBody->SetGround(true);
				while (color1 == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x -= 1;
					color1 = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
				}
				mPlayerTR->SetPos(playerPos);
			}
			else
			{
				int check = 50;
				if (mPlayer->Getsonicstate() == Sonic::eSonicState::Jump)
					check = 2;
				COLORREF colorDown = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice + check), static_cast<int>(playerPos.y + Yrevice));
				if (colorDown == GROUNDYELLO_LOOPCOURSE_RIGHT)
				{
					playerPos.x += check - 1;
					COLORREF colorUp = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
					while (colorUp == GROUNDYELLO_LOOPCOURSE_RIGHT)
					{
						playerPos.x -= 1;
						colorUp = Cicle_Rturn2->GetPixel(static_cast<int>(playerPos.x + Xrevice), static_cast<int>(playerPos.y + Yrevice));
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

	void Ground::CheckLoopStoneGround_L()
	{
		if (map_chek == 0)
		{
			COLORREF colorcheck = Cicle_Rturn->GetPixel(static_cast<int>(mPlayerTR->GetPos().x), static_cast<int>(mPlayerTR->GetPos().y) + 100);
			if (colorcheck != STONEGREY_LOOPENTER)
				return;

			if (mRotationcheck == LOOPENTERCOLOR)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
				mRotationcheck = GROUND;
			}
		}		if (map_chek == 1)
		{
			COLORREF colorcheck = Cicle_Rturn2->GetPixel(static_cast<int>(mPlayerTR->GetPos().x), static_cast<int>(mPlayerTR->GetPos().y) + 100);
			if (colorcheck != STONEGREY_LOOPENTER)
				return;

			if (mRotationcheck == LOOPENTERCOLOR)
			{
				Vector2 TempVel;
				TempVel = mPlayerRigidBody->Getgravity();
				mPlayerRigidBody->SetGravity(Vector2{ 0.0f,1000.0f });
				mRotationcheck = GROUND;
			}
		}
	}
}