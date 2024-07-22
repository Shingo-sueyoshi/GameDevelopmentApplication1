#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

//エネミー状態
enum eEnemyState
{
	IDLE,		//待機状態
	MOVE,		//移動状態
	DIE,		//イジケ状態
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
	eEnemyState enemy_state;
	eDirectionState now_direction_state;
	eDirectionState next_direction_state;
	

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	eEnemyState GetEnemyState() const;


};