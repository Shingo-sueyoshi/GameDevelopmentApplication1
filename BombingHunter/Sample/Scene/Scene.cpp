#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include"../Objects/Attack/Attack.h"
#include "../Utility/InputControl.h"
#include "DXLib.h"


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
}

Scene::~Scene()
{
	//�Y��h�~ 
	Finalize();
}

void Scene::Initialize()
{
	//�摜�Ǎ���
	back_ground = LoadGraph("Resource/images/BackGround.png");
	time_image = LoadGraph("Resource/images/TimeLimit/timer-03.png");

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

void Scene::Update()
{
	

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�J�E���g�_�E��
	count--;

	//�I�u�W�F�N�g���m�̂̓����蔻��
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Z�L�[����������A�G�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 460.0f));
	}
	//SPACE�L�[����������A���e�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Attack>(p->GetLocation());
	
	}

	//�n��&�G�ɐG�ꂽ��폜
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Delete_Object()  == TRUE)
		{
			this->objects.erase(objects.begin() + i);
		}
		
	}


}

void Scene::Draw() const
{
	//�w�i�摜��`�悷��
	//�摜�̏k��
	DrawExtendGraph(0, 0, 1000, 550, back_ground, FALSE);

	//�������ԉ摜�̕`��
	DrawExtendGraph(0, 510, 60, 550, time_image, TRUE);
	DrawExtendGraph(50, 510, 110, 550, count_image[count / 150 / 10], TRUE);
	DrawExtendGraph(100, 510, 160, 550, count_image[count / 150 % 10], TRUE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

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

