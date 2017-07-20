
// Camera �N���X

#pragma once
#include <simplemath.h>
#include <string>
#include <list>
#include "LandShape.h"
#include "Object3D.h"

class Stage 
{
private:
	// �X�e�[�W�I�u�W�F�N�g�̃f�[�^
	struct StageObjectData
	{
		std::wstring path;
		float scale;
		float rotateY;
	};
private:

	// �t�@�C��path
	const wchar_t* m_filePath;
	// ���f���̐�
	int m_modelNum;
	// ���f���̃p�X���X�g
	std::vector<std::unique_ptr<StageObjectData>>m_objData;
	std::vector<std::vector<int>>m_map;
	// ���f�����X�g
	std::vector<std::unique_ptr<LandShape>>	m_pLandShapeArray;

	// �����蔻�������Object�̃��X�g
	std::list<Object3D*> m_objectList;

private:
	// ��؂�L��
	static const wchar_t DELIMITA;
	// �}�b�v�T�C�Y
	static const DirectX::SimpleMath::Vector2 MAP_SIZE;

public:
	// �R���X�g���N�^
	Stage(const wchar_t* filePath);

	// �f�X�g���N�^
	~Stage() { Delete(); }

	// ���X�g�ɒǉ�
	void AddObject(Object3D* obj) { m_objectList.push_back(obj); }

	// �t�@�C���̓ǂݍ���
	void Load();

	// �쐬
	bool Create(const float interval);

	// �����蔻��X�V
	void ColliderUpdate();

	// �`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj);

	// �j��
	void Delete();
private:
	// ���f���f�[�^�ǂݍ���
	void LoadModel(std::wifstream* file);

	// �}�b�v�f�[�^�ǂݍ���
	void LoadMap(std::wifstream* file);
};

