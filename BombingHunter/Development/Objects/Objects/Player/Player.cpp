#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../../Objects/Enemy/BoxEnemy.h"
#include "DxLib.h"

//�R���X�g���N�^
Player::Player():animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;


}

//�f�X�g���N�^
Player::~Player()
{
}

//����������
void Player::Initialize()
{
	objecttype = PLAYER;

	//�摜�Ǎ���
	animation[0] = LoadGraph("Resource/Images/Tri-pilot/1.png");
	animation[1] = LoadGraph("Resource/Images/Tri-pilot/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("���p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Player::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);
	
	

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻�����
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y, 
		GetColor(255, 0, 0), FALSE);

#endif
}

//�I��������
void Player::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object)
{
	//����������
	if (dynamic_cast<BoxEnemy*>(hit_object) != nullptr)
	{
		radian = 3.0f;
		location = 350;
	}
}

//�ړ�����
void Player::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.0f;
		flip_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//�㉺�ړ�
	if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y += -1.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += 1.0f;
	}
	else
	{
		velocity.y = 0.0f;
	}


	//��ʊO�ɂ����Ȃ��悤�ɐ��䂷��
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((1000.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 1000.0f - (box_size.x / 2.0f);
	}

	if (location.y < (box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = box_size.y / 2.0f;
	}
	else if ((550.0f - (box_size.y / 2.0f)) < location.y)
	{
		velocity.y = 0.0f;
		location.y = 550.0f - (box_size.y / 2.0f);
	}

	//���݂̈ʒu���W�ɑ��������Z
	location += velocity;
}

//�A�j���[�V��������
void Player::AnimationControl()
{

	//�A�j���[�V�����J�E���g�����Z
	animation_count++;

	//�U�O�t���[���ɒB������
	if (animation_count >= 60)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}