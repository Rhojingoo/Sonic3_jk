#pragma once
#include "jk_Component.h"
#include"jk_Animation.h"
#include "jk_Image.h"

namespace jk
{
	class Animator : public Component
	{
	public:
		
		struct Event	//(총알같이 물체 날라가는것)
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if(mEvent)
				{
					mEvent();
				}
			}
			/*void(*name)(int, int); */ //함수포인터
			std::function<void()> mEvent;	
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

		Animator();
		virtual ~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	
		// 완성된 스프라이트 시트를 지정해서 애니메이션 제작하는함수
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop, Vector2 ChaSize, Vector2 ChaSpace
			,UINT coulmn, UINT row, UINT spriteLength
			,Vector2 offset, float duration);		
		
		// 폴더에 들어있는 파일 하나하나가 있는 스프라이트들을 이용해서 애니메이션 제작해주는 함수
		void CreateAnimations(/*const std::wstring& path, Vector2 offset, float duration*/);


		Animation* FindAnimation(const std::wstring& name);  //애니메이션 이미지 찾아는함수.
		void Play(const std::wstring& name, bool loop);		 //애니메이션재생 설정, loop 옵션으로 애니메이션 끝나면 다른장명 불러올꺼냐?

		Events* FindEvents(const std::wstring& name);

		//선생님 애니메이터 나눠진행  따라
		std::function<void()>& GetStartEevent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEevent(const std::wstring& name);
		Animation* GetActiveAnimation() { return mActiveAnimation; }
		bool IsComplte() { return mActiveAnimation->IsComplete(); }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;		//(총알같이 물체 날라가는것)
		Animation* mActiveAnimation;
		Image* mSpriteSheets;
		bool mbLoop;	
	};

}
