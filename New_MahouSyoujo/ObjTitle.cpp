//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"
#include "GameL\MultiThread.h"
#include "GameL\UserData.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag = false;//キーフラグ

	//static グローバル変数ではないが、そのような記憶寿命を持つ
	static bool init_stage = false;
	if (init_stage == false)
	{
		//プログラムを一回だけ実行する
		((UserData*)Save::GetData())->Stage = 1;
		

		for (int i = 0; i < 20; i++)
		{
			((UserData*)Save::GetData())->ScoreData[i] = 0;
			((UserData*)Save::GetData())->Clear_Flag[i] = false;
		
		}
		
		//プログラムを一回だけ実行する
		((UserData*)Save::GetData())->Diffculty = 1;

		

		//ロード
		Save::Open();//同フォルダ[UserDataからデータ取得]

		//ポーズ状態初期化
		//ロードの後に初期化しているため、前回の終了時にポーズ画面でも
		//影響を受けない。
		((UserData*)Save::GetData())->PauseMenu = false;
		((UserData*)Save::GetData())->enemyRemain = 1;


		init_stage = true;

	}

	if (init_stage == true)
	{
		Save::Seve();
	}
}

//アクション
void CObjTitle::Action()
{
	
	//エンターキーを押してシーン:ゲームMenuに移行する
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			Scene::SetScene(new CSceneMenu());
			m_key_flag = false;
		}
	}
	//デバッグ用 セーブデータ削除
	else if (Input::GetVKey('3') == true)
	{
		if (m_key_flag == true)
		{
			for (int i = 0; i < 20; i++)
			{
				((UserData*)Save::GetData())->ScoreData[i] = 0;
				((UserData*)Save::GetData())->Clear_Flag[i] = false;

			}

			((UserData*)Save::GetData())->Diffculty = 1;

			Save::Seve();

			m_key_flag = false;
		}
	}
	//デバッグ用　全ステージ開放
	else if (Input::GetVKey('4') == true)
	{
		if (m_key_flag == true)
		{
			for (int i = 0; i < 20; i++)
				((UserData*)Save::GetData())->Clear_Flag[i] = true;

			Save::Seve();

			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//0は絶対にtrueにする
	((UserData*)Save::GetData())->Clear_Flag[0] = true;

}

//ドロー
void CObjTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top =  0.0f;
	src.m_left =  0.0f;
	src.m_right = 960.0f;
	src.m_bottom = 600.0f;
	//表示位置の設定
	dst.m_top = 0.0f ;
	dst.m_left =0.0f;
	dst.m_right =800.0f;
	dst.m_bottom = 500.0f ;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
	Font::StrDraw(L"Push [Enter] Key", 280, 480, 32, c);

	if (Input::GetVKey('3') == true)
	{
		Font::StrDraw(L"セーブデータを削除しました", 0, 0, 32, c);
	}
	if (Input::GetVKey('4') == true)
	{
		Font::StrDraw(L"全ステージ開放しました。", 0, 0, 32, c);
	}
}