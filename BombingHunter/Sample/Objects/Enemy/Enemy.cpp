#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"


//コンストラクタ
Enemy::Enemy() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
	animation[5] = NULL;
	animation[6] = NULL;
	animation[7] = NULL;
	animation[8] = NULL;
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化処理
void Enemy::Initialize()
{
	objecttype = ENEMY;

	//画像読込み
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	animation[2] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[3] = LoadGraph("Resource/Images/WingEnemy/2.png");

	animation[4] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[5] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[6] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[7] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[8] = LoadGraph("Resource/Images/GoldEnemy/5.png");
	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("箱敵の画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向設定
	direction = Vector2D(1.0f, 0.0f);
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Enemy::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって反転情報を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();

}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
	DeleteGraph(animation[5]);
	DeleteGraph(animation[6]);
	DeleteGraph(animation[7]);
	DeleteGraph(animation[8]);

}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
		//当たった時
		if (hit_object->objecttype == ATTACK)
		{
			hit_damage = TRUE;
		}
}

//移動処理
void Enemy::Movement()
{
	//画面端に到達したら、進行方向を反転
	if (((location.x + direction.x) < box_size.x) ||
		(1000.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(550.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	

	//現在の位置座標に速さを加算
	location += direction;
}

//アニメーション制御
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
