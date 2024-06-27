#include "Attack.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Attack::Attack() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;

}

//デストラクタ
Attack::~Attack()
{
}

//初期化処理
void Attack::Initialize()
{
	objecttype = ATTACK;

	//画像読込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");

	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");
	

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
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

	if (location.y >= 450)
	{
		direction = 0.0f;
		ani = TRUE;  
	}

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
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);

}

//当たり判定通知処理
void Attack::OnHitCollision(GameObject* hit_object)
{

	//当たった時&地面に触れていたら爆発
		if (hit_object->objecttype == ENEMY )
		{
			direction = 0.0f;
			ani = TRUE;
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
	if (ani == TRUE)
	{
		//アニメーションカウントを加算
		animation_count++;

		//30フレームに達したら
		if (animation_count >= 8)
		{
			//カウントリセット
			animation_count = 0;

			//画像の切り替え
			if (image == animation[0])
			{
				//向きの設定
				radian = 0.0f;
				image = animation[1];
			}
			else if (image == animation[1])
			{
				image = animation[2];
			}
			else if(image == animation[2])
			{
				image = animation[3];
			}
			else 
			{
				hit_damage = TRUE;
			}

		}

	}
		
}

