#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームオーバー
class CSceneGameClear :public CScene
{
public:
	CSceneGameClear();
	~CSceneGameClear();
	void InitScene();//初期化メソッド
	void Scene();	//実行中メソッド
};