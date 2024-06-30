#pragma once
#include "../GameObject.h"

#define LINE_3  (250)

class Harpy :public GameObject
{
private:
	int animation[9];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������

public:
	Vector2D direction;			//�i�s����


public:
	Harpy();
	~Harpy();

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

	//��������
	void Way();

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimationControl();

};

