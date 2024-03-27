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

		static void InitScene();
		//static void All_Init_Sc() { AllInit_SCENE = true; }
		static bool IS_Init_Sc() { return AllInit_SCENE;}


		static void LoadScene(jk_SceneType);
		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }
		static Scene* FindScene(jk_SceneType type) { return mScenes[(UINT)type]; }

		static Scene* GetInitScene() { return mInitializeScene; }
		static void SetInitScene(Scene* scene) { mInitializeScene = scene; }

	private:
		static bool AllInit_SCENE;
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static Scene* mInitializeScene;
	};
}
