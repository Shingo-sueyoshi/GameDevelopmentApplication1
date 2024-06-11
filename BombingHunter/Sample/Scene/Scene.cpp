#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include"../Objects/Attack/Attack.h"
#include "../Utility/InputControl.h"
#include "DXLib.h"


Scene::Scene():objects()
{
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

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("Resource/images/BackGround.png������܂���\n");
	}

	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
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

	//Z�L�[����������A�G�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
	}
	//SPACE�L�[����������A���e�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<Player*>(objects[i]) != nullptr)
			{
				CreateObject<Attack>(objects[i]->GetLocation());
			}
		}
	
	}
	//�n��&�G�ɐG�ꂽ�甚��
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Delete_Object() == TRUE)
		{
			this->objects.erase(objects.begin() + i); 
		}
	}


}

void Scene::Draw() const
{
	//�w�i�摜��`�悷��
	DrawGraph(0, 0, back_ground, FALSE);

	//�摜�̏k��
	DrawExtendGraph(0, 0, 1000, 600, back_ground, FALSE);

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

