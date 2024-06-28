#pragma once
#include "../GameObject.h"

#define LINE_0  (470)

class Enemy :public GameObject
{
private:
	int animation[9];		//アニメーション画像
	int animation_count;	//アニメーション時間

public:
	Vector2D direction;			//進行方向


public:
	Enemy();
	~Enemy();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了時処理
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	//方向処理
	void Way();

private:
	//移動処理
	void Movement();

	//アニメーション制御
	void AnimationControl();

};

