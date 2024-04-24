#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy():animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize()
{
	//�摜�Ǎ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("BoxEnemy�̉摜������܂���/n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��傫��
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];
}

void Enemy::Update()
{
	location.x += 1.0f;

	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}



	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�f�o�b�N�p
#if _DEBUG
	//�����蔻�����
	Vector2D ul = location - (scale / 2.0f);
	Vector2D br = location + (scale / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	//����������
}

/*void Enemy::Movement()
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

	//���l�߂̈ʒu���W�ɑ��������Z
	location += velocity;
}*/

void Enemy::AnimationControl()
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
