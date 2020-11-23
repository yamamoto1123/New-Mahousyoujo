//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameHead.h"
#include "GameL\HitBoxManager.h"

#include "ObjDragon.h"
#include "GameL\UserData.h"

//�g�p����l�[���x�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDragon::CObjDragon(float x, float y)
{
	m_ex = x;
	m_ey = y;
}
//�C�j�V�����C�Y
void CObjDragon::Init()
{
	m_vx = 0;
	m_vy = 0;


	//block�Ƃ̏Փˏ�Ԋm�F�p
	e1_hit_up = false;
	e1_hit_down = false;
	e1_hit_left = false;
	e1_hit_right = false;

	e1_xsize = 250.0f;
	e1_ysize = 250.0f;

	a_time = 0;

	maxhp = 400;
	e_hp = maxhp;

	//�����蔻��p��HITBOX���쐬
	Hits::SetHitBox(this, m_ex, m_ey, 250, 250, ELEMENT_ENEMY, OBJ_DRAGON, 10);


	//�Q�[�W�I�u�W�F�N�g�쐬
	CObjGaugeBaseBoss* obj_gbb = new CObjGaugeBaseBoss();
	Objs::InsertObj(obj_gbb, OBJ_GAUGEBASEBOSS, 50);

	//�Q�[�W�I�u�W�F�N�g�쐬
	CObjGaugeBoss* obj_gboss = new CObjGaugeBoss();
	Objs::InsertObj(obj_gboss, OBJ_GAUGEBOSS, 51);


}

//�A�N�V����
void CObjDragon::Action()
{
	//�d��
	m_vy += 9.8 / (16.0f);


	CObjBlock* obj_block1 = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	obj_block1->BlockHit(&m_ex, &m_ey,
		&e1_hit_up, &e1_hit_down, &e1_hit_left, &e1_hit_right,
		&m_vx, &m_vy);
	//


		//HitBOx�̓��e��ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_ex, m_ey);

	a_time++;
	if (a_time >= 100)
	{
		if (a_time % 10 == 0)
		{

			CObjFireBall* obj = new CObjFireBall(m_ex, m_ey + 50.0f, -15.0f, 4.0f);
			Objs::InsertObj(obj, OBJ_FIREBALL, 49);
		}
	}

	if (a_time == 200)
	{
		a_time = 0;
	}


	if (hit->CheckObjNameHit(OBJ_SWORD) != nullptr)
	{
		CObjSword* obj_sword = (CObjSword*)Objs::GetObj(OBJ_SWORD);
		e_hp -= obj_sword->GetAttackPower();
	}
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		CObjBullet* obj_bullet = (CObjBullet*)Objs::GetObj(OBJ_BULLET);
		e_hp -= obj_bullet->GetAttackPower();
	}

	//hp��0�ɂȂ�Ə���
	if (e_hp <= 0)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);

		//Amount++;
	}
}

//�h���[
void CObjDragon::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 320.0f;
	src.m_left = 64.0f;
	src.m_right = 0.0f;
	src.m_bottom = 384.0f;
	//�\���ʒu�̐ݒ�
	dst.m_top = m_ey;
	dst.m_left = m_ex;
	dst.m_right = m_ex + 250.0f;
	dst.m_bottom = m_ey + 250.0f;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
}

int CObjDragon::GetHP()
{
	return e_hp;
}

int CObjDragon::GetMAXHP()
{
	return maxhp;
}
