#include "jk_Effect.h"

namespace jk
{
	Effect::Effect()
	{
	}
	Effect::~Effect()
	{
	}
	void Effect::Initialize()
	{
		Gameobject::Initialize();
	}
	void Effect::Update()
	{
		Gameobject::Update();
	}
	void Effect::Render(HDC hdc)
	{
		Gameobject::Render(hdc);
	}
	void Effect::Release()
	{
		Gameobject::Release();
	}
}