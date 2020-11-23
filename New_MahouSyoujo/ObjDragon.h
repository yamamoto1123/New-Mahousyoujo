#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�G�@
class CObjDragon : public CObj
{
public:
	CObjDragon(float x, float y);
	~CObjDragon() {};
	void Init();
	void Action();
	void Draw();
	int GetMAXHP();
	int GetHP();


private:
	float m_ex;
	float m_ey;
	float m_vx;
	float m_vy;


	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool e1_hit_up;
	bool e1_hit_down;
	bool e1_hit_left;
	bool e1_hit_right;

	float e1_xsize;
	float e1_ysize;

	int a_time;

	float e_hp;
	float maxhp;
};