#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include"../Objects/Attack/Attack.h"
#include "../Utility/InputControl.h"
#include "DXLib.h"


Scene::Scene() :objects(),count(0)
{
	count_image[0] = NULL;
	count_image[1] = NULL;
	count_image[2] = NULL;
	count_image[3] = NULL;
	count_image[4] = NULL;
	count_image[5] = NULL;
	count_image[6] = NULL;
	count_image[7] = NULL;
	count_image[8] = NULL;
	count_image[9] = NULL;
}

Scene::~Scene()
{
	//忘れ防止 
	Finalize();
}

void Scene::Initialize()
{
	//画像読込み
	back_ground = LoadGraph("Resource/images/BackGround.png");
	time_image = LoadGraph("Resource/images/TimeLimit/timer-03.png");

	count = TIME_LIMIT;
	count_image[0] = LoadGraph("Resource/Images/Score/0.png");
	count_image[1] = LoadGraph("Resource/Images/Score/1.png");
	count_image[2] = LoadGraph("Resource/Images/Score/2.png");
	count_image[3] = LoadGraph("Resource/Images/Score/3.png");
	count_image[4] = LoadGraph("Resource/Images/Score/4.png");
	count_image[5] = LoadGraph("Resource/Images/Score/5.png");
	count_image[6] = LoadGraph("Resource/Images/Score/6.png");
	count_image[7] = LoadGraph("Resource/Images/Score/7.png");
	count_image[8] = LoadGraph("Resource/Images/Score/8.png");
	count_image[9] = LoadGraph("Resource/Images/Score/9.png");


	//エラーチェック
	if (back_ground == -1 && time_image == -1)
	{
		throw("画像がありません\n");
	}

	int i = 0;
	for( i = 0; i <= 10 ; i++ )
	{
		if (count_image[i] == -1)
		{
			throw("画像がありません\n");
		}
	}
	//プレイヤーを生成する
	p = CreateObject<Player>(Vector2D(320.0f, 240.0f));


}

void Scene::Update()
{
	

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//カウントダウン
	count--;

	//オブジェクト同士のの当たり判定
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Zキーを押したら、敵を生成
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 460.0f));
	}
	//SPACEキーを押したら、爆弾を生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Attack>(p->GetLocation());
	
	}

	//地面&敵に触れたら削除
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Delete_Object()  == TRUE)
		{
			this->objects.erase(objects.begin() + i);
		}
		
	}


}

void Scene::Draw() const
{
	//背景画像を描画する
	//画像の縮小
	DrawExtendGraph(0, 0, 1000, 550, back_ground, FALSE);

	//制限時間画像の描画
	DrawExtendGraph(0, 510, 60, 550, time_image, TRUE);
	DrawExtendGraph(50, 510, 110, 550, count_image[count / 150 / 10], TRUE);
	DrawExtendGraph(100, 510, 160, 550, count_image[count / 150 % 10], TRUE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();

	//使用した画像を解放
	DeleteGraph(count_image[0]);
	DeleteGraph(count_image[1]);
	DeleteGraph(count_image[2]);
	DeleteGraph(count_image[3]);
	DeleteGraph(count_image[4]);
	DeleteGraph(count_image[5]);
	DeleteGraph(count_image[6]);
	DeleteGraph(count_image[7]);
	DeleteGraph(count_image[8]);
	DeleteGraph(count_image[9]);
}

#ifdef D_PIVOT_CENTER
//当たり判定チェック処理
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//二つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//二つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetLocation();
	Vector2D b_lower_right = b->GetLocation() + b->GetLocation();

	//位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().x < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER

