#pragma once
#include "jk_Scene.h"

namespace jk
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();
		static void Destroy();


		static void LoadScene(jk_SceneType);
		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }
		static Scene* FindScene(jk_SceneType type) { return mScenes[(UINT)type]; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}
