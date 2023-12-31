#include "show_bomb.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Resources.h"
#include "jk_Collider.h"
#include "jk_Object.h"
#include "jk_Pixel_Ground.h"
#include "jk_Image.h"
#include "jk_Sound.h"

#include "jk_Time.h"
#include "jk_Input.h"




namespace jk
{
	show_bomb::show_bomb(Gameobject* owner)
		: mMonspeed(3000.0f)
		, Bomber_shot(nullptr)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mGroundImage(nullptr)
		, mPixelGround(nullptr)
		, mState()
		, mOwner(owner)
		, mPos(0.f, 0.f)
		, mPlayer_pos(0.f, 0.f)
		, mCheck_Ground(0)
	{
		mImage = Resources::Load<Image>(L"Act1_3_Boomb", L"..\\Resources\\ActBG_1_3\\Act1_3_Boomber.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Act1_3_Boomb", mImage, Vector2{ 16,403 }, Vector2{ 32,32 }, Vector2{ 0.f,0.f }, 1, 1, 1, Vector2::Zero, 0.1f);
		mAnimator->CreateAnimation(L"bombing", mImage, Vector2{ 16,403 }, Vector2{ 40,32 }, Vector2{ 8.f,0.f }, 6, 1, 6, Vector2::Zero, 0.1f);
		mAnimator->GetCompleteEvent(L"bombing") = std::bind(&show_bomb::bomb, this);
		mAnimator->Play(L"Act1_3_Boomb", true);

		Bomber_shot = Resources::Load<Sound>(L"Bomber_shot", L"..\\Resources\\Sound\\Bomber_shot.wav");
	}
	show_bomb::~show_bomb()
	{
	}
	void show_bomb::Initialize()
	{
		Gameobject::Initialize();
	}
	void show_bomb::Update()
	{
		mGroundImage = mPixelGround->GetGroundImage3();
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		switch (mState)
		{
		case show_bomb::eState::Move:
			move();
			break;

		case show_bomb::eState::Death:
			death();
			break;

		default:
			break;
		}

		if (mGroundImage)
		{
			COLORREF FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(mPos.x), static_cast<int>(mPos.y) + 75));
			if (FootColor == GROUNDCOLOR)
			{
				do
				{
					mPos.y -= 1;
					FootColor = static_cast<int>(mGroundImage->GetPixel(static_cast<int>(mPos.x), static_cast<int>(mPos.y) + 75));
					tr->SetPos(mPos);
					mCheck_Ground = 1;
				} while (FootColor == GROUNDCOLOR && mPos.y > 0);
			}
		}


		Gameobject::Update();
	}
	void show_bomb::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void show_bomb::Release()
	{
		Gameobject::Release();
	}
	void show_bomb::OnCollisionEnter(Collider* other)
	{
	}
	void show_bomb::OnCollisionStay(Collider* other)
	{
	}
	void show_bomb::OnCollisionExit(Collider* other)
	{
	}
	void show_bomb::move()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		mPlayer_pos = mOwner->GetComponent<Transform>()->GetPos();
		mPos.x += 1000 * static_cast<float>(Time::DeltaTime());
		mPos.y += 500 * static_cast<float>(Time::DeltaTime());
		tr->SetPos(mPos);

		if (mCheck_Ground == 1)
		{
			Bomber_shot->Play(false);
			mState = eState::Death;
			mAnimator->Play(L"bombing", false);
		}

	}
	void show_bomb::death()
	{
	}
	void show_bomb::bomb()
	{
		object::Destory(this);
	}
}