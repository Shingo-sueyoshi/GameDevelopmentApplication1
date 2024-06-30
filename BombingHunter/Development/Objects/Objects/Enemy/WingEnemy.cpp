#include "WingEnemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"


//�R���X�g���N�^
WingEnemy::WingEnemy() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//�f�X�g���N�^
WingEnemy::~WingEnemy()
{
}

//����������
void WingEnemy::Initialize()
{
	objecttype = ENEMY;

	//�摜�Ǎ���
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("��ԓG�̉摜������܂���\n");
	}

	//
	int r = GetRand(1);

	//
	float speed = (GetRand(2) % 2 * 0.5) + 1.0f;

	//
	if (r == 1)
	{
		//�E
		direction = Vector2D(speed, 0.0f);
		this->location.x = 80.0f;
	}
	else
	{
		//��
		direction = Vector2D(-speed, 0.0f);
		this->location.x = 1000.0f;
	}


	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����̐ݒ�
	radian = 0.0f;

	//�����摜�̐ݒ�
	image = animation[0];

}

//�X�V����
void WingEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void WingEnemy::Draw() const
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
void WingEnemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);


}

//�����蔻��ʒm����
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
	//����������
	if (hit_object->objecttype == ATTACK)
	{
		score = 100;

		hit_damage = TRUE;
	}

}

//��������
void WingEnemy::Way()
{

	//
	int r = GetRand(1);

	//
	float speed = (GetRand(2) % 2 * 0.5) + 1.0f;

	//
	if (r == 1)
	{
		//�E
		direction = Vector2D(speed, 0.0f);
		location.x = 80.0f;
	}
	else
	{
		//��
		direction = Vector2D(-speed, 0.0f);
		location.x = 1000.0f;
	}
}

//�ړ�����
void WingEnemy::Movement()
{
	//��ʒ[�ɓ��B������A
	if (((location.x + direction.x) < box_size.x) ||
		(1150.0f - box_size.x) < (location.x + direction.x))
	{
		screen_damage = TRUE;
	}


	//���݂̈ʒu���W�ɑ��������Z
	location += direction;
}

//�A�j���[�V��������
void WingEnemy::AnimationControl()
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
