#pragma once

class Vector2D
{
public:
	float x;		//x���W
	float y;		//y���W

public:
	//�R���X�g���N�^
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);
	//�f�X�g���N�^
	~Vector2D();

public:
	//���Z�q�I�[�o�[���[�h
	//������Z
	Vector2D& operator = (const Vector2D& location);

	//���Z
	const Vector2D operator+(const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//���Z
	const Vector2D operator-(const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//��Z
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *=(const Vector2D& location);

	//���Z
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /=(const Vector2D& location);

	//�����l�ɃL���X�g����
	void ToInt(int* x, int* y)const;
};