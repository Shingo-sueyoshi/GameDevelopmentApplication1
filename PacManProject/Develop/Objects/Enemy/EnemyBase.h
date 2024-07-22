#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

//エネミー状態
enum eEnemyState
{
	IDLE,		//待機状態
	MOVE,		//移動状態
	DIE,		//死亡状態
};


/// <summary>
/// エネミークラス
/// </summary>
class EnemyBase : public GameObject
{
private:
	//進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};
protected:

private:
	std::vector<int> move_animation;
	std::vector<int> dying_animation;
	Vector2D velocity;
	eEnemyState Enemy_state;
	eDirectionState now_direction_state;
	eDirectionState next_direction_state;
	

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual
};