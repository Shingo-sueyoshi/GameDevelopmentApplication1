#pragma once
#include "../EnemyBase.h"

class PinkEnemy :public EnemyBase
{
private:

public:

	std::vector<int> move_animation;		// 移動のアニメーション画像

	PinkEnemy();
	~PinkEnemy();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	// 移動アニメーションの順番
	const int animation_num[2] = { 2, 3 };

public:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);
};

