#include "GameObject.h"
#include "DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	radian(0.0),
	image(0.0),
	sound(0.0),
	hit_damage(false),
	ani (false)
{
}

//�f�X�g���N�^
GameObject::~GameObject()
{
}

//����������
void GameObject::Initialize()
{
	hit_damage = false;
	ani = false;
	set_loc = false;

}

//�X�V����
void GameObject::Update()
{
}

//�`�揈��
void GameObject::Draw() const
{
	//
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif // D_PIVOT_CENTER

}

//�I��������
void GameObject::Finalize()
{
}



//�ʒm����
//�_���[�W�ʒm
bool GameObject::Delete_Object()
{
	return this->hit_damage;
}

//�_���[�W�ʒm
bool GameObject::Delete_Screen()
{
	return this->screen_damage;
}


//�A�j���[�V�����ʒm
bool GameObject::Animation_Object()
{
	return this->ani;
}

bool GameObject::Animation_Object2()
{
	return this->ani2;
}

//�X�R�A�ʒm
int GameObject::GetScore()
{
	return this->score;
}

//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//����������
}

//�ʒu���擾
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�ʒu���ݒ�
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;

}

//�{�b�N�X�T�C�Y�擾
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}