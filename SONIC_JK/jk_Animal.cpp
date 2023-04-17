#include "jk_Animal.h"
#include "jk_Transform.h"
#include "jk_Time.h"
#include "jk_Boss.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Animator.h"
#include "jk_Collider.h"
#include "jk_Scene.h"

double TimeSinceStartup()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER counter;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
	return static_cast<double>(counter.QuadPart) / static_cast<double>(frequency.QuadPart);
}


namespace jk
{
	Animal::Animal(Gameobject* owner)
	{
		mImage = Resources::Load<Image>(L"animal", L"..\\Resources\\animal.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"R_Blue_Bird", mImage, Vector2{ 166.f, 287.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"L_Blue_Bird", mImage, Vector2{ 247.f, 287.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.5f);

		mAnimator->CreateAnimation(L"R_Chicken ", mImage, Vector2{ 166.f, 331.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"L_Chicken", mImage, Vector2{ 247.f, 331.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.5f);

		mAnimator->CreateAnimation(L"R_rabit ", mImage, Vector2{ 157.f, 375.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"L_rabit", mImage, Vector2{ 246.f, 375.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 2, 1, 2, Vector2::Zero, 0.5f);

		mAnimator->CreateAnimation(L"R_penguin ", mImage, Vector2{ 138.f, 419.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"L_penguin", mImage, Vector2{ 219.f, 419.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);

		mAnimator->CreateAnimation(L"R_Wbird ", mImage, Vector2{ 141.f, 463.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);
		mAnimator->CreateAnimation(L"L_Wbird", mImage, Vector2{ 222.f, 463.f }, Vector2{ 24.f,24.f }, Vector2{ 8.f,0.f }, 3, 1, 3, Vector2::Zero, 0.5f);


		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 95.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });
		mOwner = owner;
	}
	Animal::~Animal()
	{
	}
	void Animal::Initialize()
	{
	}
	void Animal::Update()
	{		
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
				
		float time = static_cast<float>(TimeSinceStartup());
		float speed = 300.0f;  // 이동 속도
		float amplitude = 90.0f;  // 진폭
		float frequency = 2.f;  // 주파수
		pos.x -= speed * static_cast<float>(Time::DeltaTime());
		pos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());



		//std::random_device rd;
		//std::mt19937 gen(rd());
		//std::uniform_int_distribution<int> dis(0, 2);  // 0부터 2까지의 난수 생성
		//int animationIndex = dis(gen);  // 난수로 애니메이션 인덱스 선택

		//// 선택된 애니메이션 재생
		//if (animationIndex == 0)

			mAnimator->Play(L"L_Blue_Bird", true);
		//else if (animationIndex == 1)
		//	mAnimator->Play(L"L_Chicken", false);
		//else
		//	mAnimator->Play(L"L_rabit", false);


		tr->SetPos(pos);
		
	}
	void Animal::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Animal::Release()
	{
		Gameobject::Release();
	}
}

//#include <random>
//
//// ...
//
//void Animal::Update()
//{
//	Transform* tr = GetComponent<Transform>();
//	Vector2 pos = tr->GetPos();
//
//	// 시간에 따라 사인 곡선 적용
//	float time = static_cast<float>(TimeSinceStartup());
//	float speed = 100.0f;  // 이동 속도
//	float amplitude = 50.0f;  // 진폭
//	float frequency = 0.5f;  // 주파수
//	pos.x -= speed * static_cast<float>(Time::DeltaTime());
//	pos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());
//
//	// 애니메이션 랜덤 선택
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::uniform_int_distribution<int> dis(0, 2);  // 0부터 2까지의 난수 생성
//	int animationIndex = dis(gen);  // 난수로 애니메이션 인덱스 선택
//
//	// 선택된 애니메이션 재생
//	if (animationIndex == 0)
//		mAnimator->Play(L"L_Blue_Bird", true);
//	else if (animationIndex == 1)
//		mAnimator->Play(L"L_white_Bird", true);
//	else
//		mAnimator->Play(L"L_sexy_Bird", true);
//
//	tr->SetPos(pos);
//}
