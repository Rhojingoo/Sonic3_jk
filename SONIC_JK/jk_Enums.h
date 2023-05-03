#pragma once


enum class jk_SceneType
{
	Tittle,
	CharacterChoice,
	GamePlay,
	GamePlay2,
	GamePlay3,
	GamePlay4,
	//Continue,
	MiniGameplay,
	Ending,
	END
};

enum class jk_LayerType
{
	foreground,
	BG,
	BG_props,
	Ground,
	Monster,
	Bullet,
	MiniBoss,
	BOSS,
	Effect,
	Animal,
	Rings,
	Item,
	Items,
	StageSave,	
	Player2,	
	Player,
	Player_smoke,		
	UI,	
	Blend,
	End,
};


enum class jk_ComponentType
{
	Rigidbody,
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Audio,
	End,
};