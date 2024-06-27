#pragma once

#include<vector>
#include"../Objects/GameObject.h"

//マクロ定義
#define TIME_LIMIT (3000*3)

class Scene
{
private:
	class Player* p;
	std::vector<GameObject*>objects;		//オブジェクトリスト

	//画像変数
	int back_ground;

	int time_image;				//時間画像
	int count_image[10];		//数字画像
	int count;				//時間

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();

		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("ゲームオブジェクトが生成できませんでした\n");

		}
		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);
	
		//インスタンスのポインタを返却
		return new_instance;

	}
};

