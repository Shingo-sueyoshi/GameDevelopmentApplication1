#include "Attack.h"
#include "Attack.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Attack::Attack() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//�f�X�g���N�^
Attack::~Attack()
{
}

//����������
void Attack::Initialize()
{
	//�摜�Ǎ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	//animation[1] = LoadGraph("Resource/Images/BoxAttack/2.png");

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
	direction = Vector2D(1.0f, -0.5f);
}

//�X�V����
void Attack::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Attack::Draw() const
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
void Attack::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

}

//�����蔻��ʒm����
void Attack::OnHitCollision(GameObject* hit_object)
{
	//����������
	direction = 0.0f;
}

//�ړ�����
void Attack::Movement()
{
	
}

//�A�j���[�V��������
void Attack::AnimationControl()
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