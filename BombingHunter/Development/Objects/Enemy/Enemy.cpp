#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Enemy::Enemy():animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化処理
void Enemy::Initialize()
{
	//画像読込み
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("BoxEnemyの画像がありません/n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定大きさ
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];
}

void Enemy::Update()
{
	location.x += 1.0f;

	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}



	//アニメーション制御
	AnimationControl();
}

//描画処理
void Enemy::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//デバック用
#if _DEBUG
	//当たり判定可視化
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif
}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時
}

/*void Enemy::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.0f;
		flip_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//下冤罪の位置座標に速さを加算
	location += velocity;
}*/

void Enemy::AnimationControl()
{

	//アニメーションカウントを加算
	animation_count++;

	//６０フレームに達したら
	if (animation_count >= 60)
	{
		//カウントリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
