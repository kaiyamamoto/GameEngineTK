#include "pch.h"
#include "Stage.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PlayerRobot.h"
#include "EnemyRobot.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的変数宣言
// 区切り記号
const wchar_t Stage::DELIMITA = L',';
const int Stage::MAP_SIZE_X = 10;
const int Stage::MAP_SIZE_Y = 10;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="filePath">ファイルのパス</param>
Stage::Stage(const wchar_t* filePath)
	:m_filePath(filePath)
{
}

/// <summary>
/// ファイルの読み込み
/// </summary>
void Stage::Load()
{
	wifstream ifs(m_filePath);
	wstring line;

	// 1行スキップ
	getline(ifs, line);
	// モデルpathデータ読み込み
	LoadModel(&ifs);
	// 1行スキップ
	getline(ifs, line);
	// マップデータ読み込み
	LoadMap(&ifs);
}

/// <summary>
/// 作成
/// </summary>
/// <param name="fileName">ファイルのパス</param>
/// <param name="interval">間隔</param>
/// <returns>作成の成功失敗</returns>
bool Stage::Create(const float interval)
{
	// vector初期化
	m_pLandShapeArray.clear();

	// 作成
	for (int i = 0; i < MAP_SIZE_Y; i++){
		for (int j = 0; j < MAP_SIZE_X; j++){
			// モデル作成
			std::auto_ptr<LandShape> landshape(new LandShape());

			StageObjectData* data = m_objData[m_map[i][j]].get();

			// 読み込む
			const wchar_t* path = data->path.c_str();
			landshape->Initialize(path, path);

			// スケール反映
			landshape->SetScale(data->scale);

			// ｙ回転反映
			Vector3 rot = landshape->GetEulerAngle();
			rot.y = data->rotateY;
			landshape->SetEulerAngle(rot);

			// ライト無効
			landshape->DisableLighting();

			// 座標
			landshape->SetPosition(Vector3(static_cast<float>(j)*interval, 0.0f, static_cast<float>(i)*interval));
			landshape->Update();
			// コンテナに追加
			m_pLandShapeArray.push_back(std::move(landshape));
		}
	}
	return true;
}

void Stage::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)
{
	// 地形の描画
	for (auto itr = m_pLandShapeArray.begin(); itr != m_pLandShapeArray.end(); ++itr) {
		(*itr)->Draw(state, view, proj);
	}
}

/// <summary>
/// 破棄
/// </summary>
void Stage::Delete()
{
	// ローカルなvector　関数を出たら消える
	std::vector<std::shared_ptr<LandShape>>array;
	// swap で入れ替える
	m_pLandShapeArray.swap(array);
	// ローカルなvectorは自動的に破棄される
}

/// <summary>
/// モデルpathの読み込み
/// </summary>
/// <param name="file">読み込み中のファイル</param>
void Stage::LoadModel(wifstream* file)
{
	wstring line;

	// モデルの数取得
	getline(*file, line);
	m_modelNum = stoi(line.c_str());

	// Pathリストのサイズ調整
	m_objData.resize(m_modelNum);

	// 各行のデータを解析
	for (int i = 0; i < m_modelNum; i++) {
		// モデル
		wstring fileName;
		wstring arrayNumStr;

		// 一行読み込み
		getline(*file, line);

		// 1行分を文字列ストリームに変換
		wstringstream stream(line);

		// ファイル名の文字列を読み込み
		getline(stream, fileName, DELIMITA);

		// 要素番号読み取り
		getline(stream, arrayNumStr, DELIMITA);
		int arrayNum;
		arrayNum = stoi(arrayNumStr.c_str());

		// データ作成
		m_objData[arrayNum] = make_unique<StageObjectData>();

		// スケール読み取り
		getline(stream, arrayNumStr, DELIMITA);
		float scale = static_cast<float>(stod(arrayNumStr.c_str()));
		m_objData[arrayNum]->scale = scale;

		// y回転読み取り
		getline(stream, arrayNumStr, DELIMITA);
		float rotY = static_cast<float>(stod(arrayNumStr.c_str()));
		m_objData[arrayNum]->rotateY = rotY;

		// Pathリストに追加
		m_objData[arrayNum]->path = fileName;
	}
}

/// <summary>
/// マップデータの読み込み
/// </summary>
/// <param name="file">読み込み中のファイル</param>
void Stage::LoadMap(wifstream* file)
{
	//データ読み込み用
	wstring str;
	int data[MAP_SIZE_X * MAP_SIZE_Y];
	wstring token;

	int dataCnt = 0;

	//csvのデータをカンマを飛ばして読み込む
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		getline(*file, str);
		wstringstream stream(str);
		for (int j = 0; j < MAP_SIZE_X; j++) {
			getline(stream, token, DELIMITA);
			data[dataCnt] = stoi(token.c_str());
			dataCnt++;
		}
	}
	// データを代入
	dataCnt = 0;
	// 配列確保
	m_map = vector<vector<int>>(MAP_SIZE_Y, vector<int>(MAP_SIZE_X));
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			// データを代入
			m_map[i][j] = data[dataCnt];
			dataCnt++;
		}
	}
	return;
}
