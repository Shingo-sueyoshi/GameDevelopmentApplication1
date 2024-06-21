#include "count.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

// コンストラクタ
Count::Count() :count(0)
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

//デストラクタ
Count::~Count()
{
}

//初期化処理
void Count::Initialize()
{
	count = TIME_LIMIT;

	count_image[0] = LoadGraph("Resource/Images/Score/0.ping");
	count_image[1] = LoadGraph("Resource/Images/Score/1.ping");
	count_image[2] = LoadGraph("Resource/Images/Score/2.ping");
	count_image[3] = LoadGraph("Resource/Images/Score/3.ping");
	count_image[4] = LoadGraph("Resource/Images/Score/4.ping");
	count_image[5] = LoadGraph("Resource/Images/Score/5.ping");
	count_image[6] = LoadGraph("Resource/Images/Score/6.ping");
	count_image[7] = LoadGraph("Resource/Images/Score/7.ping");
	count_image[8] = LoadGraph("Resource/Images/Score/8.ping");
	count_image[9] = LoadGraph("Resource/Images/Score/9.ping");
	
	
	////エラーチェック
	//int i = NULL;

	//if (count_image[i] == -1)
	//{
	//	for (i = 0; i < 10; i++)
	//	{
	//	throw("時間の画像がありません\n");
	//	}

	//}

	


}

//更新処理
void Count::Update()
{
	//
	count--;
	
	//アニメーション制御
	AnimationControl();


}

//描画処理
void Count::Draw() const
{
	//タイム画像の描画

	DrawExtendGraph(100, 100, 150, 150, count_image[count / 150], FALSE);
}

//終了時処理
void Count::Finalize()
{
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

//アニメーション制御
void Count::AnimationControl()
{
}
