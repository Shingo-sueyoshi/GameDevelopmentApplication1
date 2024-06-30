#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER		//マクロ定義
#define PLAYER		(1)		//
#define ENEMY		(2)		//
#define ATTACK		(3)		//

//オブジェクトの親クラス（基底クラス）
class GameObject
{
protected:
	Vector2D location;		//位置情報
	Vector2D box_size;		//矩形の大きさ
	double radian;			//向き
	int image;				//描画する画像
	int sound;				//再生する音源

	int score;				//スコア

	bool hit_damage;		//当たり通知変数
	bool screen_damage;
	bool ani;
	bool ani2;
	bool set_loc;

public:
	int objecttype;			//キャラ箱

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

	int GetScore();					//スコア取得処理

	bool Delete_Object();				//当たり通知処理
	bool Delete_Screen();
	bool Animation_Object();				//当たり通知処理
	bool Animation_Object2();
	


public:
	virtual void OnHitCollision(GameObject* hit_object);		//当たり判定通知処理

	Vector2D GetLocation() const;								//位置情報取得（Vector2D）
	void SetLocation(const Vector2D& location);					//位置情報変更処理

	//当たり判定の大きさを取得
	Vector2D GetBoxSize() const;

};

