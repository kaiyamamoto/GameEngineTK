
// Camera クラス

#pragma once
#include <simplemath.h>
#include <string>
#include <list>
#include "LandShape.h"
#include "Robot.h"

class Robot;

class Stage 
{
private:
	// ステージオブジェクトのデータ
	struct StageObjectData
	{
		std::wstring path;
		float scale;
		float rotateY;
	};
private:
	// ファイルpath
	const wchar_t* m_filePath;
	// モデルの数
	int m_modelNum;
	// モデルのパスリスト
	std::vector<std::unique_ptr<StageObjectData>>m_objData;
	std::vector<std::vector<int>>m_map;
	// モデルリスト
	std::vector<std::shared_ptr<LandShape>>	m_pLandShapeArray;

private:
	// 区切り記号
	static const wchar_t DELIMITA;
	// マップサイズ
	static const int MAP_SIZE_X;
	static const int MAP_SIZE_Y;

	// 排斥ベクトル一時的保存領域
	Vector3 m_evenReject;
	Vector3 m_verticalReject;
public:
	// コンストラクタ
	Stage(const wchar_t* filePath);

	// デストラクタ
	~Stage() { Delete(); }

	// ファイルの読み込み
	void Load();

	// 作成
	bool Create(const float interval);

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj);

	// 破棄
	void Delete();

	// 
	std::vector<std::shared_ptr<LandShape>>	GetLandshape() { return m_pLandShapeArray; }

	//// 水平のあたり判定
	//Vector3* EvenCollision(Robot* robot);

	//// 垂直のあたり判定
	//float VerticalCollision(Robot* robot);

private:
	// モデルデータ読み込み
	void LoadModel(std::wifstream* file);

	// マップデータ読み込み
	void LoadMap(std::wifstream* file);
};

