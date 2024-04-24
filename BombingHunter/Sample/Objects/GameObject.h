#pragma once

#include "../Utility/Vector2D.h"


//オブジェクトの親クラス（基底クラス）
class GameObject
{
protected:
	Vector2D location;		//色情報
	double scale;			//大きさ
	double radian;			//向き
	int image;		//描画する画像
	int sound;		//再生する音源

public:

	//コンストラクタ
	GameObject();
	//デストラクタ
	virtual~GameObject();		//仮想関数化

	//仮想関数にする
	virtual void Initialize();			//初期化処理
	virtual void Update();				//更新処理
	virtual void Draw() const;			//描画処理
	virtual void Finalize();			//終了時処理

public:
	virtual void OnHitCollision(GameObject* hit_object);		//当たり判定通知処理

	Vector2D GetLocation() const;								//位置情報取得（Vector2D）
	void SetLocation(const Vector2D& location);					//位置情報変更処理

};

