#pragma once
#include "jk_Component.h"
#include"jk_Animation.h"
#include "jk_Image.h"

namespace jk
{
	class Animator : public Component
	{
	public:
		
		struct Event	//(�Ѿ˰��� ��ü ���󰡴°�)
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
			/*void(*name)(int, int); */ //�Լ�������
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

	
		// �ϼ��� ��������Ʈ ��Ʈ�� �����ؼ� �ִϸ��̼� �����ϴ��Լ�
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop, Vector2 ChaSize, Vector2 ChaSpace
			,UINT coulmn, UINT row, UINT spriteLength
			,Vector2 offset, float duration);		
		
		// ������ ����ִ� ���� �ϳ��ϳ��� �ִ� ��������Ʈ���� �̿��ؼ� �ִϸ��̼� �������ִ� �Լ�
		void CreateAnimations(/*const std::wstring& path, Vector2 offset, float duration*/);


		Animation* FindAnimation(const std::wstring& name);  //�ִϸ��̼� �̹��� ã�ƴ��Լ�.
		void Play(const std::wstring& name, bool loop);		 //�ִϸ��̼���� ����, loop �ɼ����� �ִϸ��̼� ������ �ٸ���� �ҷ��ò���?

		Events* FindEvents(const std::wstring& name);

		//������ �ִϸ����� ��������  ����
		std::function<void()>& GetStartEevent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEevent(const std::wstring& name);
		Animation* GetActiveAnimation() { return mActiveAnimation; }
		bool IsComplte() { return mActiveAnimation->IsComplete(); }

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;		//(�Ѿ˰��� ��ü ���󰡴°�)
		Animation* mActiveAnimation;
		Image* mSpriteSheets;
		bool mbLoop;	
	};

}
