#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"


//�R���X�g���N�^
Enemy::Enemy() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
	animation[5] = NULL;
	animation[6] = NULL;
	animation[7] = NULL;
	animation[8] = NULL;
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//����������
void Enemy::Initialize()
{
	objecttype = ENEMY;

	//�摜�Ǎ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	animation[2] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[3] = LoadGraph("Resource/Images/WingEnemy/2.png");

	animation[4] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	animation[5] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	animation[6] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	animation[7] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	animation[8] = LoadGraph("Resource/Images/GoldEnemy/5.png");
	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("���G�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����ݒ�
	direction = Vector2D(1.0f, 0.0f);
}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���Ĕ��]�������肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
	DeleteGraph(animation[5]);
	DeleteGraph(animation[6]);
	DeleteGraph(animation[7]);
	DeleteGraph(animation[8]);

}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
		//����������
		if (hit_object->objecttype == ATTACK)
		{
			hit_damage = TRUE;
		}
}

//�ړ�����
void Enemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]
	if (((location.x + direction.x) < box_size.x) ||
		(1000.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(550.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	

	//���݂̈ʒu���W�ɑ��������Z
	location += direction;
}

//�A�j���[�V��������
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
