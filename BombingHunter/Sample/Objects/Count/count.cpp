#include "count.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

// �R���X�g���N�^
Count::Count() :count(0)
{
	count_image[0] = NULL;
	count_image[1] = NULL;
	count_image[2] = NULL;
	count_image[3] = NULL;
	count_image[4] = NULL;
	count_image[5] = NULL;
	count_image[6] = NULL;
	count_image[7] = NULL;
	count_image[8] = NULL;
	count_image[9] = NULL;
}

//�f�X�g���N�^
Count::~Count()
{
}

//����������
void Count::Initialize()
{
	count_image[0] = LoadGraph("Resource/Images/Score/0.ping");
	count_image[1] = LoadGraph("Resource/Images/Score/1.ping");
	count_image[2] = LoadGraph("Resource/Images/Score/2.ping");
	count_image[3] = LoadGraph("Resource/Images/Score/3.ping");
	count_image[4] = LoadGraph("Resource/Images/Score/4.ping");
	count_image[5] = LoadGraph("Resource/Images/Score/5.ping");
	count_image[6] = LoadGraph("Resource/Images/Score/6.ping");
	count_image[7] = LoadGraph("Resource/Images/Score/7.ping");
	count_image[8] = LoadGraph("Resource/Images/Score/8.ping");
	count_image[9] = LoadGraph("Resource/Images/Score/9.ping");
	
	
	//�G���[�`�F�b�N
	int i = NULL;

	if (count_image[i] == -1)
	{
		for (i = 0; i < 10; i++)
		{
		throw("���Ԃ̉摜������܂���\n");
		}

	}

	


}

//�X�V����
void Count::Update()
{
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Count::Draw() const
{
	//�^�C���摜�̕`��
	DrawRotaGraphF(900, 100, 0.8, radian, image, TRUE);
}

//�I��������
void Count::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(count_image[0]);
	DeleteGraph(count_image[1]);
	DeleteGraph(count_image[2]);
	DeleteGraph(count_image[3]);
	DeleteGraph(count_image[4]);
	DeleteGraph(count_image[5]);
	DeleteGraph(count_image[6]);
	DeleteGraph(count_image[7]);
	DeleteGraph(count_image[8]);
	DeleteGraph(count_image[9]);
}

//�A�j���[�V��������
void Count::AnimationControl()
{
}
