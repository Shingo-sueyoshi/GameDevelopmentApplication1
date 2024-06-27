#pragma once

#include<vector>
#include"../Objects/GameObject.h"

//�}�N����`
#define TIME_LIMIT (3000*3)

class Scene
{
private:
	class Player* p;
	std::vector<GameObject*>objects;		//�I�u�W�F�N�g���X�g

	//�摜�ϐ�
	int back_ground;

	int time_image;				//���ԉ摜
	int count_image[10];		//�����摜
	int count;				//����

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();

		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");

		}
		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);
	
		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;

	}
};

