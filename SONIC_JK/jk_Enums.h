#pragma once


enum class jk_SceneType
{
	Tittle,
	CharacterChoice,
	GamePlay,
	GamePlay2,
	Contunue,
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
	BOSS,
	Bullet,
	MiniBoss,
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