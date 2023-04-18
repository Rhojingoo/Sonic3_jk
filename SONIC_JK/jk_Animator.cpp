#include "jk_Animator.h"
#include "jk_Resources.h"


namespace jk
{
	Animator::Animator()
		:Component(jk_ComponentType::Animator)
		, mActiveAnimation(nullptr)
		, mSpriteSheets(nullptr)
		, mbLoop(false)
		
	{
	}

	Animator::~Animator()
	{
		for (auto animation : mAnimations)
		{
			delete animation.second;
			animation.second = nullptr;
		}
		for (auto events : mEvents)
		{
			delete events.second;
			events.second = nullptr;
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			if(mActiveAnimation->IsComplete())
			{
				Animator::Events* events
					= FindEvents(mActiveAnimation->GetName());

				if (events != nullptr)
					events->mCompleteEvent();
			}
			if (mbLoop && mActiveAnimation->IsComplete())
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void Animator::Release()
	{
	}

	void Animator::CreateAnimation(const std::wstring& name, Image* sheet, Vector2 leftTop, Vector2 ChaSize, Vector2 ChaSpace, UINT coulmn, UINT row, UINT spriteLength, Vector2 offset, float duration)
	{
		Animation* animation = FindAnimation(name);

		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->Create(sheet, leftTop, ChaSize, ChaSpace, coulmn, row, spriteLength, offset, duration);
		animation->SetName(name);
		animation->SetAnimator(this);
		animation->SetAnimationName(name);

		mAnimations.insert(std::make_pair(name, animation));
		Events* event = new Events();
		mEvents.insert(std::make_pair(name, event));
	}

	void Animator::CreateAnimations()
	{
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::Play(const std::wstring& name, bool loop)
	{
		//원래코드
	/*	mActiveAnimation = FindAnimation(name);
		mbLoop = loop;*/

		if (mActiveAnimation != nullptr)
		{
			Animator::Events* prevEvents
				= FindEvents(mActiveAnimation->GetName());

			if (prevEvents != nullptr)
			{
				prevEvents->mEndEvent();
			}
		}
			mActiveAnimation = FindAnimation(name);
			mActiveAnimation->Reset();
			mbLoop = loop;

			Animator::Events* events
				= FindEvents(mActiveAnimation->GetName());

			if (events != nullptr)
			{
				events->mStartEvent();
			}	
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{	
		
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
		{
			return nullptr;
		}		
		return iter->second;
	}

	//선생님 애니메이터 나눠진행  따라
	std::function<void()>& Animator::GetStartEevent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);
		Animator::Events* events
			= FindEvents(animation->GetAnimationName());

		return events->mStartEvent.mEvent;
	}

		//선생님 애니메이터 나눠진행  따라
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);
		Animator::Events* events
			= FindEvents(animation->GetAnimationName());

		return events->mCompleteEvent.mEvent;
	}

	//선생님 애니메이터 나눠진행  따라
	std::function<void()>& Animator::GetEndEevent(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);
		Animator::Events* events
			= FindEvents(animation->GetAnimationName());

		return events->mEndEvent.mEvent;
	}
}