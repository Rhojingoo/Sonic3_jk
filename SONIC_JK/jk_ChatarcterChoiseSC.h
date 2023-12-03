#pragma once
#include "jk_Scene.h"
#include "jk_Image.h"
#include "jk_Sound.h"

namespace jk
{
	class ChatarcterChoiseSC : public Scene
	{
	public:
		ChatarcterChoiseSC();
		~ChatarcterChoiseSC();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;


		void CreateBlending();

	private:
		Image* mScenImage;
		Sound* choice_music;
		Sound* Act1_music;
		Sound* Selec;
	};
}