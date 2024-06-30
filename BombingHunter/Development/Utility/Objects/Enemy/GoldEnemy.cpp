#include "GoldEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"


//コンストラクタ
GoldEnemy::GoldEnemy() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//デストラクタ
GoldEnemy::~GoldEnemy()
{
}

//初期化処理
void GoldEnemy::Initialize()
{
	objecttype = ENEMY;

	//画像読込み
	animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");


	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1 || animation[4] == -1)
	{
		throw("ゴールド敵の画像がありません\n");
	}

	//
	int r = GetRand(1);

	//
	float speed = (GetRand(2) % 2 * 1.5) + 1.0f;

	//
	if (r == 1)
	{
		//右
		direction = Vector2D(speed, 0.0f);
		this->location.x = 80.0f;
	}
	else
	{
		//左
		direction = Vector2D(-speed, 0.0f);
		this->location.x = 1000.0f;
	}


	//当たり判定の大きさを設定
	box_size = 64.0f;

	//向きの設定
	radian = 0.0f;

	//初期画像の設定
	image = animation[0];

}

//更新処理
void GoldEnemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void GoldEnemy::Draw() const
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
void GoldEnemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);


}

//当たり判定通知処理
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時
	if (hit_object->objecttype == ATTACK)
	{
		score = 1000;

		hit_damage = TRUE;
	}
}

//方向処理
void GoldEnemy::Way()
{

	//
	int r = GetRand(1);

	//
	float speed = (GetRand(2) % 2 * 0.5) + 1.0f;

	//
	if (r == 1)
	{
		//右
		direction = Vector2D(speed, 0.0f);
		location.x = 80.0f;
	}
	else
	{
		//左
		direction = Vector2D(-speed, 0.0f);
		location.x = 1000.0f;
	}
}

//移動処理
void GoldEnemy::Movement()
{
	//画面端に到達したら、
	if (((location.x + direction.x) < box_size.x) ||
		(1150.0f - box_size.x) < (location.x + direction.x))
	{
		screen_damage = TRUE;
	}


	//現在の位置座標に速さを加算
	location += direction;
}

//アニメーション制御
void GoldEnemy::AnimationControl()
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
		else if (image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else
		{
			image = animation[4];
		}
		
	}
}
