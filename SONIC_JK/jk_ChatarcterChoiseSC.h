#pragma once
#include "jk_Scene.h"


namespace jk
{
	class Image;
	class Sound;
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