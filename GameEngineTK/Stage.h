
// Camera クラス

#pragma once
#include <simplemath.h>
#include <string>
#include <list>
#include "LandShape.h"
#include "Object3D.h"

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
	std::vector<std::unique_ptr<LandShape>>	m_pLandShapeArray;

	// あたり判定をするObjectのリスト
	std::list<Object3D*> m_objectList;

private:
	// 区切り記号
	static const wchar_t DELIMITA;
	// マップサイズ
	static const DirectX::SimpleMath::Vector2 MAP_SIZE;

public:
	// コンストラクタ
	Stage(const wchar_t* filePath);

	// デストラクタ
	~Stage() { Delete(); }

	// リストに追加
	void AddObject(Object3D* obj) { m_objectList.push_back(obj); }

	// ファイルの読み込み
	void Load();

	// 作成
	bool Create(const float interval);

	// あたり判定更新
	void ColliderUpdate();

	// 描画
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj);

	// 破棄
	void Delete();
private:
	// モデルデータ読み込み
	void LoadModel(std::wifstream* file);

	// マップデータ読み込み
	void LoadMap(std::wifstream* file);
};

