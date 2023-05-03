#include "jk_Act1_Water.h"
#include "jk_Water_effect.h"

#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "Rigidbody.h"
#include "jk_Collider.h"
#include "jk_Resources.h"
#include "jk_Time.h"
#include "jk_Input.h"
#include "jk_Object.h"
#include "jk_Camera.h"


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
		Vector2 size = collider->GetSize();
		collider->SetCenter(Vector2{ (-0.0f) * size.x, (-0.f) * size.y });

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
			Water_Splashes(sonic_pos.x, sonic_pos.y+50);
		}

		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			Vector2 tails_pos = tails->GetComponent<Transform>()->GetPos();
			Water_Splashes(tails_pos.x, tails_pos.y + 40);
		}
	}

	void Act1_Water::OnCollisionStay(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
			mSonic_rb->SetGravity(Vector2{ 0.f,500.f });
			Transform* sonicTr = sonic->GetComponent<Transform>();
			Vector2 sonic_Pos = sonicTr->GetPos();

			if ((sonic->Getsonicstate() == Sonic::eSonicState::Jump) || (sonic->Getsonicstate() == Sonic::eSonicState::Hurt))
			{
				Vector2 velocity = mSonic_rb->GetVelocity();
				velocity.y = -450.0f;

				mSonic_rb->SetVelocity(velocity);
				mSonic_rb->SetGround(false);

				sonic_Pos = sonicTr->GetPos();
				sonicTr->SetPos(sonic_Pos);
			}
		}
		
		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			Rigidbody* tails_rb = tails->GetComponent<Rigidbody>();
			tails_rb->SetGravity(Vector2{ 0.f,500.f });
			Transform* tailsTr = tails->GetComponent<Transform>();
			Vector2 tails_Pos = tailsTr->GetPos();

			if ((tails->GetTails_state() == Tails::eTailsState::Jump) || (tails->GetTails_state() == Tails::eTailsState::Movejump) || (tails->GetTails_state() == Tails::eTailsState::Hurt))
			{
				Vector2 velocity = tails_rb->GetVelocity();
				velocity.y = -450.0f;

				tails_rb->SetVelocity(velocity);
				tails_rb->SetGround(false);

				tails_Pos = tailsTr->GetPos();
				tailsTr->SetPos(tails_Pos);
			}
		}


		//tails_State
	}

	void Act1_Water::OnCollisionExit(Collider* other)
	{
		if (Sonic* sonic = dynamic_cast<Sonic*>(other->GetOwner()))
		{
			Vector2 sonic_pos = sonic->GetComponent<Transform>()->GetPos();
			Water_Splashes(sonic_pos.x, sonic_pos.y+60);

			Rigidbody* mSonic_rb = sonic->GetComponent<Rigidbody>();
			mSonic_rb->SetGravity(Vector2{ 0.f,1000.f });
			mSonic_rb->AddForce(Vector2{ 0.f,-150.f });
		}


		if (Tails* tails = dynamic_cast<Tails*>(other->GetOwner()))
		{
			Vector2 tails_pos = tails->GetComponent<Transform>()->GetPos();
			Water_Splashes(tails_pos.x, tails_pos.y + 50);

			Rigidbody* tails_rb = tails->GetComponent<Rigidbody>();
			tails_rb->SetGravity(Vector2{ 0.f,1000.f });
			tails_rb->AddForce(Vector2{ 0.f,-150.f });
		}

	}


	void Act1_Water::Water_Splashes(float a, float b)
	{		
		Scene* curScene = SceneManager::GetActiveScene();
		Water_effect* water_effect = new Water_effect();
		water_effect->GetComponent<Transform>()->SetPos(Vector2{ a,b });
		curScene->AddGameobeject(water_effect, jk_LayerType::BG_props);
	}
}
