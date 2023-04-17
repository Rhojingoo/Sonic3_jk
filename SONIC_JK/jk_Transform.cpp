#include "jk_Transform.h"


namespace jk
{
	Transform::Transform()
		:Component(jk_ComponentType::Transform)
		, mPos(Vector2::Zero)	
		, mScale(Vector2::One)
		, Dir(0)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::Render(HDC hdc)
	{
	}

	void Transform::Release()
	{
	}

}

