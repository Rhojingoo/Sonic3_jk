#include "jk_Act1_Water.h"
#include "jk_Time.h"
#include "jk_SceneManager.h"
#include "jk_Input.h"
#include "jk_Resources.h"
#include "jk_Transform.h"
#include "jk_Object.h"
#include "jk_Collider.h"
#include "jk_Camera.h"
#include "jk_Water_effect.h"
#include "jk_SONIC.h"

namespace jk
{
	Act1_Water::Act1_Water()
	{
	}
	Act1_Water::~Act1_Water()
	{
	}
	void Act1_Water::Initialize()
	{
		mImage = Resources::Load<Image>(L"AcT1_WATER", L"..\\Resources\\AcT1_WATER.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		tr->SetPos(Vector2{ 21240.f,  3936.f });

		float pos_y = mImage->GetHeight() * 3.5;
		float pos_x = mImage->GetWidth() * 3;

		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(pos_x, pos_y));		
		//Vector2 size = collider->GetSize();
		//collider->SetCenter(Vector2{ (-0.0f) * size.x, (-0.f) * size.y });

		Gameobject::Initialize();
	}
	void Act1_Water::Update()
	{
		Gameobject::Update();
	}
	void Act1_Water::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		checktime = 120.0f;
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = (BYTE)checktime;
		Vector2 mpos = Camera::CaluatePos(pos);
		
		AlphaBlend(hdc,  mpos.x, mpos.y, mImage->GetWidth()*3, mImage->GetHeight()*3.5, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	
		Gameobject::Render(hdc);
	}
	void Act1_Water::Release()
	{
		Gameobject::Release();
	}

	void Act1_Water::OnCollisionEnter(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{			
			Vector2 sonic_pos = sonic->GetComponent<Transform>()->GetPos();
			Scene* curScene = SceneManager::GetActiveScene();			
			Water_effect* water_effect = new Water_effect();
			water_effect->GetComponent<Transform>()->SetPos(Vector2{ sonic_pos.x,sonic_pos.y  });
			curScene->AddGameobeject(water_effect, jk_LayerType::BG_props);			
		}
	}

	void Act1_Water::OnCollisionStay(Collider* other)
	{

	}

	void Act1_Water::OnCollisionExit(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Vector2 sonic_pos = sonic->GetComponent<Transform>()->GetPos();
			Scene* curScene = SceneManager::GetActiveScene();
			Water_effect* water_effect = new Water_effect();
			water_effect->GetComponent<Transform>()->SetPos(Vector2{ sonic_pos.x,sonic_pos.y  });
			curScene->AddGameobeject(water_effect, jk_LayerType::BG_props);
		}
	}
}
