#pragma once
#include "../GameObject.h"
class Attack :public GameObject
{
private:
	int animation[4];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������

	
	Vector2D direction;			//�i�s����


public:
	Attack();
	~Attack();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update() override;
	//�`�揈��
	virtual void Draw() const override;
	//�I��������
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();

public:
	//�A�j���[�V��������
	void AnimationControl();
};


