#pragma once
#include "../EnemyBase.h"

class PinkEnemy :public EnemyBase
{
private:

public:

	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜

	PinkEnemy();
	~PinkEnemy();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	// �ړ��A�j���[�V�����̏���
	const int animation_num[2] = { 2, 3 };

public:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);
};

