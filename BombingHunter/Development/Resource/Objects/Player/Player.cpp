#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Objects/Enemy/BoxEnemy.h"
#include "DxLib.h"

//コンストラクタ
Player::Player():animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;


}

//デストラクタ
Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{
	objecttype = PLAYER;

	//画像読込み
	animation[0] = LoadGraph("Resource/Images/Tri-pilot/1.png");
	animation[1] = LoadGraph("Resource/Images/Tri-pilot/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("鳥パイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Player::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);
	
	

	//デバック用
#if _DEBUG
	//当たり判定可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y, 
		GetColor(255, 0, 0), FALSE);

#endif
}

//終了時処理
void Player::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{
	//当たった時
	if (dynamic_cast<BoxEnemy*>(hit_object) != nullptr)
	{
		radian = 3.0f;
		location = 350;
	}
}

//移動処理
void Player::Movement()
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

	//上下移動
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y += -1.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += 1.0f;
	}
	else
	{
		velocity.y = 0.0f;
	}


	//画面外にいかないように制御する
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((1000.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 1000.0f - (box_size.x / 2.0f);
	}

	if (location.y < (box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = box_size.y / 2.0f;
	}
	else if ((550.0f - (box_size.y / 2.0f)) < location.y)
	{
		velocity.y = 0.0f;
		location.y = 550.0f - (box_size.y / 2.0f);
	}

	//現在の位置座標に速さを加算
	location += velocity;
}

//アニメーション制御
void Player::AnimationControl()
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
