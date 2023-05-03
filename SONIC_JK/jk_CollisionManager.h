#pragma once
#include "CommonInclude.h"
#include "jk_Enums.h"
#include "jk_Collider.h"

namespace jk
{
	union ColliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	class Scene;
	class CollisionManager
	{
	public:
		static void Update();
		static void LayerCollision(Scene* scene, jk_LayerType left, jk_LayerType right);
		static void ColliderCollision(Collider* leftCol, Collider* rightCol, jk_LayerType left, jk_LayerType right);
		static bool Intersect(Collider* left, Collider* right);

		static void SetLayer(jk_LayerType left, jk_LayerType right, bool value);
		static void Clear();

	private:
		static UINT mMatrix[(UINT)jk_LayerType::End];
		static std::map<UINT64, bool> mCollisionMap;
		
	};
}