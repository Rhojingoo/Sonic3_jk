#include "jk_CollisionManager.h"
#include "jk_Scene.h"
#include "jk_SceneManager.h"
#include "jk_Transform.h"
#include "jk_Component.h"
#include "jk_Gameobject.h"

int frame_check = 0;

namespace jk
{	
	WORD CollisionManager::mMatrix[(UINT)jk_LayerType::End] = {};	
	std::map<UINT64, bool>CollisionManager::mCollisionMap;

	void CollisionManager::Update()
	{		
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)jk_LayerType::End;row++)		
		{
			for (UINT col = 0; col < (UINT)jk_LayerType::End; col++)			
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(scene, (jk_LayerType)row, (jk_LayerType)col);
				}
			}
		}	
	}

	void CollisionManager::LayerCollision(Scene* scene, jk_LayerType left, jk_LayerType right)
	{
		std::vector<Gameobject* >  lefts = scene->GetGameobjects(left);// lefts = scene->GetGameobjects(left);-> �տ� ������ ����
		std::vector<Gameobject*> rights = scene->GetGameobjects(right);// rights = scene->GetGameobjects(left);-> �տ� ������ ����
		for (auto leftobject : lefts)
		{
			if (leftobject == nullptr)
				continue;
			Collider* leftcollider = leftobject->GetComponent<Collider>();
			if (leftcollider == nullptr)
				continue;


			for (auto rightobject : rights)
			{
				Collider* rightcollider = rightobject->GetComponent<Collider>();
				if (rightcollider == nullptr)
					continue;

				if (leftobject == rightobject)
				continue;
			
				ColliderCollision(leftcollider, rightcollider, left, right);		
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* leftCol, Collider* rightCol, jk_LayerType left, jk_LayerType right)
	{
		if ((int)left == 2 && (int)right == 11)
			int a = 0;
		ColliderID colliderID = {};
		colliderID.left = (UINT)leftCol->GetID();
		colliderID.right = (UINT)rightCol->GetID();

		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(colliderID.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		if (Intersect(leftCol, rightCol))
		{
			//���� �浹 ���۽� enter
			if (iter->second == false)
			{
				leftCol->OnCollisionEnter(rightCol);
				rightCol->OnCollisionEnter(leftCol);				
			}
			else // �浹���� ���� stay
			{
				leftCol->OnCollisionStay(rightCol);
				rightCol->OnCollisionStay(leftCol);
			}
			iter->second = true;
		}
		else
		{
			//Exit
			//���������� �浹 ��
			//����� �浹 x
			if (iter->second == true)
			{
				leftCol->OnCollisionExit(rightCol);
				rightCol->OnCollisionExit(leftCol);

				iter->second = false;
			}		
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* tr = left->GetOwner()->GetComponent<Transform>();
		Transform* tr1 = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos_tr = tr->GetPos();
		Vector2 rightPos_tr = tr1->GetPos();


			Vector2 leftPos = left->Getpos();
			Vector2 rightPos = right->Getpos();
		

			Vector2 leftSize = left->GetSize();
			Vector2 rightSize = right->GetSize();


			leftPos.x = leftPos.x + leftSize.x / 2.0f;
			leftPos.y = leftPos.y + leftSize.y / 2.0f;

			rightPos.x = rightPos.x + rightSize.x / 2.0f;
			rightPos.y = rightPos.y + rightSize.y / 2.0f;

			if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
			{
				return true;
			}						
	
		return false;
	}
	//	Vector2 L_mCenter = left->GetCenter();
	//	Vector2 R_mCenter = right->GetCenter();

	//if (fabs(leftPos.x/* + L_mCenter.x*/- rightPos.x/*+ R_mCenter.x*/) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
	//	&& fabs(leftPos.y /*+ L_mCenter.y*/ - rightPos.y/*+ R_mCenter.y*/) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
	//{
	//	return true;//����� �ߴ��� �ɾ� �浹�Ǵ��� Ȯ�ΰ���
	//}

	void CollisionManager::SetLayer(jk_LayerType left, jk_LayerType right, bool value)
	{
		UINT row = 0;
		UINT col = 0;

		UINT ileft = (UINT)left;
		UINT iright = (UINT)right;

		if (left <= right)
		{
			row = ileft;
			col = iright;
		}
		else
		{
			row = iright;
			col = ileft;
		}

		if (value == true)
			mMatrix[row] |= (1 << col);
		else
			mMatrix[row] &= ~(1 << col);
	}

	void CollisionManager::Clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * (UINT)jk_LayerType::End);
		mCollisionMap.clear();
	}
}