#include "jk_Animal.h"
#include "jk_SceneManager.h"
#include "jk_Image.h"
#include "jk_Animator.h"
#include "jk_Scene.h"
#include "jk_Transform.h"
#include "jk_Collider.h"
#include "jk_Resources.h"

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
		: mOwner(owner)
		, mImage(nullptr)
		, mAnimator(nullptr)
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
		mAnimator->Play(L"L_Blue_Bird", true);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(90.0f, 95.0f));
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.10f) * size.x, (-0.11f) * size.y });		
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
		float speed = 300.0f;
		float amplitude = 90.0f; 
		float frequency = 2.f;  
		pos.x -= speed * static_cast<float>(Time::DeltaTime());
		pos.y += amplitude * sin(frequency * time) * static_cast<float>(Time::DeltaTime());		

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
