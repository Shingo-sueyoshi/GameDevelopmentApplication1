#include "Scene.h"
#include"../Objects/GameObject.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/BoxEnemy.h"
#include "../Objects/Enemy/WingEnemy.h"
#include "../Objects/Enemy/GoldEnemy.h"
#include "../Objects/Harpy/Harpy.h"
#include"../Objects/Attack/Attack.h"
#include "../Utility/InputControl.h" 
#include "DXLib.h"

//�R���X�g���N�^
Scene::Scene() :objects(),count(0)
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

	result_image[0] = NULL;
	result_image[1] = NULL;
	result_image[2] = NULL;
	result_image[3] = NULL;
	result_image[4] = NULL;

}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~ 
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�摜�Ǎ���
	back_ground = LoadGraph("Resource/images/BackGround.png");
	time_image = LoadGraph("Resource/images/TimeLimit/timer-03.png");
	score_image = LoadGraph("Resource/images/Score/font-21.png");


	count = TIME_LIMIT;
	count_image[0] = LoadGraph("Resource/Images/Score/0.png");
	count_image[1] = LoadGraph("Resource/Images/Score/1.png");
	count_image[2] = LoadGraph("Resource/Images/Score/2.png");
	count_image[3] = LoadGraph("Resource/Images/Score/3.png");
	count_image[4] = LoadGraph("Resource/Images/Score/4.png");
	count_image[5] = LoadGraph("Resource/Images/Score/5.png");
	count_image[6] = LoadGraph("Resource/Images/Score/6.png");
	count_image[7] = LoadGraph("Resource/Images/Score/7.png");
	count_image[8] = LoadGraph("Resource/Images/Score/8.png");
	count_image[9] = LoadGraph("Resource/Images/Score/9.png");

	result_image[0] = LoadGraph("Resource/Images/Evaluation/Finish.png");
	result_image[1] = LoadGraph("Resource/Images/Evaluation/OK.png");
	result_image[2] = LoadGraph("Resource/Images/Evaluation/BAD.png");
	result_image[3] = LoadGraph("Resource/Images/Evaluation/GOOD.png");
	result_image[4] = LoadGraph("Resource/Images/Evaluation/Perfect.png");

	image = result_image[0];


	//�G���[�`�F�b�N
	if (back_ground == -1 && time_image == -1)
	{
		throw("�摜������܂���\n");
	}

	int i = 0;
	for( i = 0; i <= 10 ; i++ )
	{
		if (count_image[i] == -1)
		{
			throw("�摜������܂���\n");
		}
	}
	//�v���C���[�𐶐�����
	p = CreateObject<Player>(Vector2D(320.0f, 240.0f));




}

//�X�V����
void Scene::Update()
{
	

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�J�E���g�_�E��
	if (count <= 0)
	{
		ResultScene();
	}
	else
	{
		count--;
	}
	


	//�I�u�W�F�N�g���m�̂̓����蔻��
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	////�����_���ŁA�G�𐶐�

	f_count++;

	if (f_count>=120)
	{
		//�����_���֐��ݒ�
		R_Enemy = GetRand(5);


		if (R_Enemy == 0)
		{
			BoxEnemy* n = CreateObject<BoxEnemy>(Vector2D(0.0f, LINE_0));			///���������Z�b�g���P�[�V���������ʂɂȂ��Ă�
			n->Way();
		}
		else if (R_Enemy == 1)
		{
			WingEnemy* n = CreateObject<WingEnemy>(Vector2D(0.0f, LINE_1));
			n->Way();
		}
		else if (R_Enemy == 2)
		{
			GoldEnemy* n = CreateObject<GoldEnemy>(Vector2D(0.0f, LINE_2));
			n->Way();
		}
		else if (R_Enemy == 3)
		{
			Harpy* n = CreateObject<Harpy>(Vector2D(0.0f, LINE_3));
			n->Way();
		}
		
		f_count = 0;

	}

	//SPACE�L�[����������A���e�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Attack>(p->GetLocation());
	
	}

	//�G�ɐG�ꂽ��폜
	for (int i = 0; i < objects.size(); i++)
	{
		
		if (objects[i]->Delete_Object()  == TRUE)
		{
			total_score += objects[i]->GetScore();

			this->objects.erase(objects.begin() + i);
		}
		if (total_score < 0)
		{
			total_score = 0;
		}
	}

	//��ʊO�ɍs������폜
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Delete_Screen() == TRUE)
		{
			this->objects.erase(objects.begin() + i);
		}

	}

}

//���U���g�\��
void Scene::ResultScene()
{
	//�v�f�̍폜
	objects.clear();

	//�t���[���J�E���g�̉��Z
	result_count++;

	if (result_count >= 300)
	{
		if (total_score <= 1500)
		{
			image = result_image[2];
		}
		else if (total_score <= 2000)
		{
			image = result_image[1];
		}
		else if (total_score <= 2500)
		{
			image = result_image[3];
		}
		else 
		{
			image = result_image[4];
		}

		//�J�E���g���Z�b�g
		result_count = 0;
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜��`�悷��
	//�摜�̏k��
	DrawExtendGraph(0, 0, 1000, 550, back_ground, FALSE);

	//�������ԉ摜�̕`��
	DrawExtendGraph(0, 510, 60, 550, time_image, TRUE);
	DrawExtendGraph(50, 510, 110, 550, count_image[count / 150 / 10], TRUE);
	DrawExtendGraph(100, 510, 160, 550, count_image[count / 150 % 10], TRUE);

	//�X�R�A�`��
	DrawExtendGraph(200, 510, 400, 550, score_image, TRUE);

	DrawExtendGraph(450, 510, 470, 550, count_image[total_score / 1000], TRUE);
	DrawExtendGraph(470, 510, 490, 550, count_image[(total_score % 1000)/100 ], TRUE);
	DrawExtendGraph(490, 510, 510, 550, count_image[(total_score % 1000 %100) /10   ], TRUE);
	DrawExtendGraph(510, 510, 530, 550, count_image[(total_score % 1000 %100) %10 ], TRUE);


	//���Ԍo�߂�Finish��\��
	if (count <= 0)
	{
		DrawRotaGraphF(530, 200, 0.5, 0.0, image, TRUE, FALSE);
	}



	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();

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

#ifdef D_PIVOT_CENTER
//�����蔻��`�F�b�N����
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//��̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//��̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetLocation();
	Vector2D b_lower_right = b->GetLocation() + b->GetLocation();

	//�ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().x < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER

