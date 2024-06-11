#pragma once
#include "../GameObject.h"
class Count :public GameObject
{
private:
	int count_image[10];		//時間画像
	int count;				//時間

public:
	Count();
	~Count();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了時処理
	virtual void Finalize() override;

private:
	//アニメーション制御
	void AnimationControl();
};


