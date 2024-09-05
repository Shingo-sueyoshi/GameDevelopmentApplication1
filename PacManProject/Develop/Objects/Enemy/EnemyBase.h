#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// �v���C���[���
enum eEnemyState
{
	ENEMY_IDLE,		// �ҋ@���
	ENEMY_MOVE,		// �ړ����
	ENEMY_IZIKE,		// �C�W�P���
	ENEMY_DIE,		// ���S���
};

/// <summary>
/// �G�l�~�[�N���X�i�p�b�N�}���j
/// </summary>
class EnemyBase : public GameObject
{
private:
	// �i�s�������
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

protected:
	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜
	std::vector<int> eye_animation;		// �ڂ̃A�j���[�V�����摜
	Vector2D old_location;					// �O��� location
	Vector2D velocity;						// �ړ���
	eEnemyState enemy_state;				// �G�l�~�[���
	eDirectionState now_direction_state;	// ���ݐi�s�������
	eDirectionState next_direction_state;	// ����i�s�������
	int food_count;							// �a��H�ׂ���
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	int eye;
	ePanelID old_panel;						// �O��p�l�����
	bool is_power_down;						// �p���[�a��H�ׂ����H
	bool is_izike;						// ���񂾏�ԂɂȂ������H

	// �ړ��A�j���[�V�����̏���
	const int animation_num[2] = { 0, 1};

	const int animation_izike[2] = { 16, 17};

	////�ڂ̃A�j���[�V�����̏���
	//const int animation_num_eye[];

public:

	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// �a��H�ׂ����擾
	/// </summary>
	/// <returns>�a��H�ׂ���</returns>
	int GetFoodCount() const;

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	void SetEnemyState();

	/// <summary>
	/// �p���[�_�E��������
	/// </summary>
	void SetPowerDown();


protected:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void AnimationControl(float delta_second);
};
