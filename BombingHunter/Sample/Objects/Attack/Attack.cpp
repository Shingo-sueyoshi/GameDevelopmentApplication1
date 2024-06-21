#include "Attack.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Attack::Attack() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//デストラクタ
Attack::~Attack()
{
}

//初期化処理
void Attack::Initialize()
{
	//画像読込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("爆弾の画像がありません\n");
	}

	//向きの設定
	radian = 1.6f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向設定
	direction = Vector2D(0.0f, 1.0f);
}

//更新処理
void Attack::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Attack::Draw() const
{

	//爆弾画像の描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE);

	//親クラスの描画処理を呼び出す
	__super::Draw();

}

//終了時処理
void Attack::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

//当たり判定通知処理
void Attack::OnHitCollision(GameObject* hit_object)
{
	//当たった時
	if (dynamic_cast<Attack*>(hit_object) != nullptr)
	{
		Hit_damage = FALSE;
	}
	else if (dynamic_cast<Attack*>(hit_object) != nullptr)
	{
		Hit_damage = FALSE;
	}
	else
	{
		Hit_damage = TRUE;
	}

}

//移動処理
void Attack::Movement()
{
	//現在の位置座標に速さを加算
	location += direction; 
}

//アニメーション制御
void Attack::AnimationControl()
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
			image = animation[0];
		}
		else
		{
			image = animation[0];
		}
	}
}
