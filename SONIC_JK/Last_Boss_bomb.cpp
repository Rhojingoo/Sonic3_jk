#include "Last_Boss_bomb.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"
#include "jk_Object.h"
#include "jk_Image.h"

namespace jk
{
	Last_Boss_bomb::Last_Boss_bomb(Gameobject* owner)
		: mOwner(owner)
		, mImage(nullptr)
		, mAnimator(nullptr)
		, mState(eBossState::Move)
	{
		mImage = Resources::Load<Image>(L"last_bomb", L"..\\Resources\\ROBOT.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"last_bomb", mImage, Vector2{ 625,1118 }, Vector2{ 116,88 }, Vector2{ 4,0 }, 9, 1, 9, Vector2::Zero, 0.1f);
		mAnimator->Play(L"last_bomb", false);
		mAnimator->GetCompleteEvent(L"last_bomb") = std::bind(&Last_Boss_bomb::complete_bomb, this);

		mOwner = owner;
	}
	Last_Boss_bomb::~Last_Boss_bomb()
	{
	}
	void Last_Boss_bomb::Initialize()
	{
		Gameobject::Initialize();
	}
	void Last_Boss_bomb::Update()
	{
		Transform* tr = GetComponent<Transform>();

		switch (mState)
		{
		case jk::Last_Boss_bomb::eBossState::Move:move();
			break;

		case jk::Last_Boss_bomb::eBossState::Death:death();
			break;

		default:
			break;
		}

		Gameobject::Update();
	}
	void Last_Boss_bomb::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Last_Boss_bomb::Release()
	{
		Gameobject::Release();
	}
	void Last_Boss_bomb::move()
	{
	}
	void Last_Boss_bomb::death()
	{	
		object::Destory(this);
	}
	void Last_Boss_bomb::complete_bomb()
	{
		mState = eBossState::Death;		
	}
}