#pragma once

#include "../Utility/Vector2D.h"


//�I�u�W�F�N�g�̐e�N���X�i���N���X�j
class GameObject
{
protected:
	unsigned int color;		//�F���
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//box_size���

public:

	//�R���X�g���N�^
	GameObject();
	//�f�X�g���N�^
	virtual~GameObject();		//���z�֐���

	//���z�֐��ɂ���
	virtual void Initialize();			//����������
	virtual void Update();				//�X�V����
	virtual void Draw() const;			//�`�揈��
	virtual void Finalize();			//�I��������

public:
	virtual void OnHitCollision(GameObject* hit_object);		//����������
	Vector2D GetLocation() const;								//�ʒu���擾�iVector2D�j
	void SetLocation(const Vector2D& location);					//�ʒu���ύX����

};

