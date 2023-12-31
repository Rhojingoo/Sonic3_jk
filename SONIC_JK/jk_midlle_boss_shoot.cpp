#include "jk_midlle_boss_shoot.h"
#include "jk_SceneManager.h"
#include "jk_Scene.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Image.h"



namespace jk
{
		midlle_boss_shoot::midlle_boss_shoot()
			: mCenterpos(30792.f, 2407.f)
			, mPos(0.f,0.f)
			, mMonspeed(120.0f)
			, mMonmaxdistance(100.0f)
			, fDist(0.f)
			, mImage(nullptr)
			, mAnimator(nullptr)
			, mState()
			
		{
			mImage = Resources::Load<Image>(L"middle_bos", L"..\\Resources\\middle_bos.bmp");
			mAnimator = AddComponent<Animator>();
			mAnimator->CreateAnimation(L"middle_bos_shoot_show", mImage, Vector2{ 296.f,360.f }, Vector2{ 24.f,32.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.1f);
			mAnimator->Play(L"middle_bos_shoot_show", true);
		}
		midlle_boss_shoot::~midlle_boss_shoot()
		{
		}
		void midlle_boss_shoot::Initialize()
		{
			Gameobject::Initialize();
		}
		void midlle_boss_shoot::Update()
		{
			Transform* tr = GetComponent<Transform>();
			mPos = tr->GetPos();

			switch (mState)
			{
			case jk::midlle_boss_shoot::eState::Move:move();
				break;

			case jk::midlle_boss_shoot::eState::Attack:attack();
				break;

			case jk::midlle_boss_shoot::eState::Death:death();
				break;

			default:
				break;
			}
			Gameobject::Update();
		}
		void midlle_boss_shoot::Render(HDC hdc)
		{
			Gameobject::Render(hdc);
		}
		void midlle_boss_shoot::Release()
		{
			Gameobject::Release();
		}
		void midlle_boss_shoot::OnCollisionEnter(Collider* other)
		{
		}
		void midlle_boss_shoot::OnCollisionStay(Collider* other)
		{
		}
		void midlle_boss_shoot::OnCollisionExit(Collider* other)
		{
		}
		void midlle_boss_shoot::move()
		{
			Transform* tr = GetComponent<Transform>();

			fDist = mCenterpos.y - mPos.y - mMonmaxdistance;
			mPos.y -= mMonspeed * static_cast<float>(Time::DeltaTime());
				
			tr->SetPos(mPos);
		}
		void midlle_boss_shoot::attack()
		{
		}
	
		void midlle_boss_shoot::death()
		{
		}
}