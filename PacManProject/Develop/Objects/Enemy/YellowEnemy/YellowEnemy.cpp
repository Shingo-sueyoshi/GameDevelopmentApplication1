#include "YellowEnemy.h"
#include "../../Utility/ResourceManager.h"

YellowEnemy::YellowEnemy()
{
}

YellowEnemy::~YellowEnemy()
{
}

void YellowEnemy::Initialize()
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Initialize();

	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);


	image = move_animation[6];
}

void YellowEnemy::Update(float delta_second)
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Update(delta_second);
}

void YellowEnemy::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void YellowEnemy::Finalize()
{
	
}

void YellowEnemy::Movement(float delta_second)
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Movement(delta_second);
}

void YellowEnemy::AnimationControl(float delta_second)
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::AnimationControl(delta_second);

	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		image = move_animation[animation_num[animation_count]];

	}
}
