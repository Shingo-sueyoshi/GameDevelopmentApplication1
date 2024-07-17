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
/// エネミークラス（アカベエ）
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

public:
	EnemyBase();
	virtual ~EnemyBase();
};