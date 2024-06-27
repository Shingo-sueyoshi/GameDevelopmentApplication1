#include "Attack.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Attack::Attack() :animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;

}

//�f�X�g���N�^
Attack::~Attack()
{
}

//����������
void Attack::Initialize()
{
	objecttype = ATTACK;

	//�摜�Ǎ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");

	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");
	

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("���e�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 1.6f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����ݒ�
	direction = Vector2D(0.0f, 1.0f);
}

//�X�V����
void Attack::Update()
{
	//�ړ�����
	Movement();

	if (location.y >= 450)
	{
		direction = 0.0f;
		ani = TRUE;  
	}

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Attack::Draw() const
{

	//���e�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, image, TRUE);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

//�I��������
void Attack::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);

}

//�����蔻��ʒm����
void Attack::OnHitCollision(GameObject* hit_object)
{

	//����������&�n�ʂɐG��Ă����甚��
		if (hit_object->objecttype == ENEMY )
		{
			direction = 0.0f;
			ani = TRUE;
		}
		
		
}

//�ړ�����
void Attack::Movement()
{
	//���݂̈ʒu���W�ɑ��������Z
	location += direction;
	
}

//�A�j���[�V��������
void Attack::AnimationControl()
{
	if (ani == TRUE)
	{
		//�A�j���[�V�����J�E���g�����Z
		animation_count++;

		//30�t���[���ɒB������
		if (animation_count >= 8)
		{
			//�J�E���g���Z�b�g
			animation_count = 0;

			//�摜�̐؂�ւ�
			if (image == animation[0])
			{
				//�����̐ݒ�
				radian = 0.0f;
				image = animation[1];
			}
			else if (image == animation[1])
			{
				image = animation[2];
			}
			else if(image == animation[2])
			{
				image = animation[3];
			}
			else 
			{
				hit_damage = TRUE;
			}

		}

	}
		
}

