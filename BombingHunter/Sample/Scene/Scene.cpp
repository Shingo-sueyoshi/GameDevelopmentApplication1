#include "Scene.h"

#include "../Objects/Player/Player.h"

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

}

void Scene::Draw() const
{
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
