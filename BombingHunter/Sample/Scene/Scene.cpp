#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include"../Objects/Attack/Attack.h"
#include "../Utility/InputControl.h"
#include "DXLib.h"


Scene::Scene():objects()
{
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

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/BackGround.pngがありません\n");
	}

	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

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
		CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
	}
	//SPACEキーを押したら、爆弾を生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<Player*>(objects[i]) != nullptr)
			{
				CreateObject<Attack>(objects[i]->GetLocation());
			}
		}
	
	}
	//地面&敵に触れたら爆風
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Delete_Object() == TRUE)
		{
			this->objects.erase(objects.begin() + i); 
		}
	}


}

void Scene::Draw() const
{
	//背景画像を描画する
	DrawGraph(0, 0, back_ground, FALSE);

	//画像の縮小
	DrawExtendGraph(0, 0, 1000, 600, back_ground, FALSE);

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

