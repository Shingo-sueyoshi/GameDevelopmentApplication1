#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER		//�}�N����`
#define PLAYER		(1)		//
#define ENEMY		(2)		//
#define ATTACK		(3)		//

//�I�u�W�F�N�g�̐e�N���X�i���N���X�j
class GameObject
{
protected:
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//��`�̑傫��
	double radian;			//����
	int image;				//�`�悷��摜
	int sound;				//�Đ����鉹��

	int score;				//�X�R�A

	bool hit_damage;		//������ʒm�ϐ�
	bool screen_damage;
	bool ani;
	bool ani2;
	bool set_loc;

public:
	int objecttype;			//�L������

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

	int GetScore();					//�X�R�A�擾����

	bool Delete_Object();				//������ʒm����
	bool Delete_Screen();
	bool Animation_Object();				//������ʒm����
	bool Animation_Object2();
	


public:
	virtual void OnHitCollision(GameObject* hit_object);		//�����蔻��ʒm����

	Vector2D GetLocation() const;								//�ʒu���擾�iVector2D�j
	void SetLocation(const Vector2D& location);					//�ʒu���ύX����

	//�����蔻��̑傫�����擾
	Vector2D GetBoxSize() const;

};

