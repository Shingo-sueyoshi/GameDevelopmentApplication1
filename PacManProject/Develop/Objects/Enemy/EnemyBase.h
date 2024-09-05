#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// プレイヤー状態
enum eEnemyState
{
	ENEMY_IDLE,		// 待機状態
	ENEMY_MOVE,		// 移動状態
	ENEMY_IZIKE,		// イジケ状態
	ENEMY_DIE,		// 死亡状態
};

/// <summary>
/// エネミークラス（パックマン）
/// </summary>
class EnemyBase : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> eye_animation;		// 目のアニメーション画像
	Vector2D old_location;					// 前回の location
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// エネミー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	int food_count;							// 餌を食べた数
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	int eye;
	ePanelID old_panel;						// 前回パネル情報
	bool is_power_down;						// パワー餌を食べたか？
	bool is_izike;						// 死んだ状態になったか？

	// 移動アニメーションの順番
	const int animation_num[2] = { 0, 1};

	const int animation_izike[2] = { 16, 17};

	////目のアニメーションの順番
	//const int animation_num_eye[];

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

public:
	/// <summary>
	/// 餌を食べた数取得
	/// </summary>
	/// <returns>餌を食べた数</returns>
	int GetFoodCount() const;

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	void SetEnemyState();

	/// <summary>
	/// パワーダウンさせる
	/// </summary>
	void SetPowerDown();


protected:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	virtual void AnimationControl(float delta_second);
};
