#pragma once
#include "../EnemyBase.h"

class RedEnemy :public EnemyBase
{
private:

public:

	RedEnemy();
	~RedEnemy();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

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

