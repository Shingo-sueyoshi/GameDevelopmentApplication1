#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

Player::Player():animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

Player::~Player()
{
}

void Player::Initialize()
{
	//画像読込み
	animation[0] = LoadGraph("Resource/Image/Tri-pilot/1.png");
	animation[1] = LoadGraph("Resource/Image/Tri-pilot/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("鳥パイロットの画像がありません/n");
	}

	//
	radian = 0.0f;

	//
	box_size = Vector2D(64.0f);

	//
	image = animation[0];
}

void Player::Update()
{
	//
	Movement();

	//
	AnimationControl();
}

void Player::Draw() const
{
	//
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//
#if _DEBUG
	//
	Vector2D ul = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif
}

void Player::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

void Player::OnHitCollision(GameObject* hit_object)
{
	//
}

void Player::Movement()
{
	//
	Vector2D velocity = 0.0f;

	//
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_LEFT)
	{
		velocity.x += 1.0f;
		flip_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//
	location += veloctiy;
}

void Player::AnimationControl()
{
}
