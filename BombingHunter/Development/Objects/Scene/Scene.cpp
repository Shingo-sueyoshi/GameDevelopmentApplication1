#include "Scene.h"
#include"../Objects/GameObject.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/BoxEnemy.h"
#include "../Objects/Enemy/WingEnemy.h"
#include "../Objects/Enemy/GoldEnemy.h"
#include "../Objects/Harpy/Harpy.h"
#include"../Objects/Attack/Attack.h"
#include "../Utility/InputControl.h" 
#include "DXLib.h"

//コンストラクタ
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

	result_image[0] = NULL;
	result_image[1] = NULL;
	result_image[2] = NULL;
	result_image[3] = NULL;
	result_image[4] = NULL;

}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止 
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//画像読込み
	back_ground = LoadGraph("Resource/images/BackGround.png");
	time_image = LoadGraph("Resource/images/TimeLimit/timer-03.png");
	score_image = LoadGraph("Resource/images/Score/font-21.png");


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

	result_image[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	result_image[1] = LoadGraph("Resource/Images/Evaluation/OK.png");
	result_image[2] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	result_image[3] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	result_image[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

	image = result_image[0];


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

//更新処理
void Scene::Update()
{
	

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//カウントダウン
	if (count <= 0)
	{
		ResultScene();
	}
	else
	{
		count--;
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

	////ランダムで、敵を生成

	f_count++;

	if (f_count>=120)
	{
		//ランダム関数設定
		R_Enemy = GetRand(5);


		if (R_Enemy == 0)
		{
			BoxEnemy* n = CreateObject<BoxEnemy>(Vector2D(0.0f, LINE_0));			///もう少しセットロケーションが無駄になってる
			n->Way();
		}
		else if (R_Enemy == 1)
		{
			WingEnemy* n = CreateObject<WingEnemy>(Vector2D(0.0f, LINE_1));
			n->Way();
		}
		else if (R_Enemy == 2)
		{
			GoldEnemy* n = CreateObject<GoldEnemy>(Vector2D(0.0f, LINE_2));
			n->Way();
		}
		else if (R_Enemy == 3)
		{
			Harpy* n = CreateObject<Harpy>(Vector2D(0.0f, LINE_3));
			n->Way();
		}
		
		f_count = 0;

	}

	//SPACEキーを押したら、爆弾を生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Attack>(p->GetLocation());
	
	}

	//敵に触れたら削除
	for (int i = 0; i < objects.size(); i++)
	{
		
		if (objects[i]->Delete_Object()  == TRUE)
		{
			total_score += objects[i]->GetScore();

			this->objects.erase(objects.begin() + i);
		}
		if (total_score < 0)
		{
			total_score = 0;
		}
	}

	//画面外に行ったら削除
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Delete_Screen() == TRUE)
		{
			this->objects.erase(objects.begin() + i);
		}

	}

}

//リザルト表示
void Scene::ResultScene()
{
	//要素の削除
	objects.clear();

	//フレームカウントの加算
	result_count++;

	if (result_count >= 300)
	{
		if (total_score <= 1500)
		{
			image = result_image[2];
		}
		else if (total_score <= 2000)
		{
			image = result_image[1];
		}
		else if (total_score <= 2500)
		{
			image = result_image[3];
		}
		else 
		{
			image = result_image[4];
		}

		//カウントリセット
		result_count = 0;
	}
}

//描画処理
void Scene::Draw() const
{
	//背景画像を描画する
	//画像の縮小
	DrawExtendGraph(0, 0, 1000, 550, back_ground, FALSE);

	//制限時間画像の描画
	DrawExtendGraph(0, 510, 60, 550, time_image, TRUE);
	DrawExtendGraph(50, 510, 110, 550, count_image[count / 150 / 10], TRUE);
	DrawExtendGraph(100, 510, 160, 550, count_image[count / 150 % 10], TRUE);

	//スコア描画
	DrawExtendGraph(200, 510, 400, 550, score_image, TRUE);

	DrawExtendGraph(450, 510, 470, 550, count_image[total_score / 1000], TRUE);
	DrawExtendGraph(470, 510, 490, 550, count_image[(total_score % 1000)/100 ], TRUE);
	DrawExtendGraph(490, 510, 510, 550, count_image[(total_score % 1000 %100) /10   ], TRUE);
	DrawExtendGraph(510, 510, 530, 550, count_image[(total_score % 1000 %100) %10 ], TRUE);


	//時間経過でFinishを表示
	if (count <= 0)
	{
		DrawRotaGraphF(530, 200, 0.5, 0.0, image, TRUE, FALSE);
	}



	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
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

