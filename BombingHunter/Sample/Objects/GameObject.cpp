#include "GameObject.h"
#include "DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	radian(0.0),
	image(0.0),
	sound(0.0),
	hit_damage(false),
	ani (false)
{
}

//デストラクタ
GameObject::~GameObject()
{
}

//初期化処理
void GameObject::Initialize()
{
	hit_damage = false;
	ani = false;
	set_loc = false;

}

//更新処理
void GameObject::Update()
{
}

//描画処理
void GameObject::Draw() const
{
	//
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif // D_PIVOT_CENTER

}

//終了時処理
void GameObject::Finalize()
{
}



//通知処理
//ダメージ通知
bool GameObject::Delete_Object()
{
	return this->hit_damage;
}

//ダメージ通知
bool GameObject::Delete_Screen()
{
	return this->screen_damage;
}


//アニメーション通知
bool GameObject::Animation_Object()
{
	return this->ani;
}

bool GameObject::Animation_Object2()
{
	return this->ani2;
}

//スコア通知
int GameObject::GetScore()
{
	return this->score;
}

//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時
}

//位置情報取得
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//位置情報設定
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;

}

//ボックスサイズ取得
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}
