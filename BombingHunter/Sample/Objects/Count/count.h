#pragma once
#include "../GameObject.h"
#define TIME_LIMIT (3000*3)

class Count :public GameObject
{
private:
	int count_image[10];		//���ԉ摜
	int count;				//����

public:
	Count();
	~Count();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update() override;
	//�`�揈��
	virtual void Draw() const override;
	//�I��������
	virtual void Finalize() override;

private:
	//�A�j���[�V��������
	void AnimationControl();
};


