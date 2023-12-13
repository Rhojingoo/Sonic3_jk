#pragma once
#include "jk_Resource.h"

namespace jk
{
	class Sound : public Resource
	{
	public:
		virtual HRESULT Load(const std::wstring& path) override;
		bool LoadWavFile(const std::wstring& path);
		void Play(bool loop);
		void Stop(bool reset);
		void SetPosition(float position, bool loop);
		void SetVolume(float volume);
		int GetDecibel(float volume);

	private:
		LPDIRECTSOUNDBUFFER		mSoundBuffer = nullptr;
		DSBUFFERDESC			mBufferDesc = {};
		int mVolume = 0;
	};
}
