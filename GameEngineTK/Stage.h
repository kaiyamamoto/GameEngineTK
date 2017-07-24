
// Camera �N���X

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
	std::vector<std::shared_ptr<LandShape>>	m_pLandShapeArray;

private:
	// ��؂�L��
	static const wchar_t DELIMITA;
	// �}�b�v�T�C�Y
	static const int MAP_SIZE_X;
	static const int MAP_SIZE_Y;

	// �r�˃x�N�g���ꎞ�I�ۑ��̈�
	Vector3 m_evenReject;
	Vector3 m_verticalReject;
public:
	// �R���X�g���N�^
	Stage(const wchar_t* filePath);

	// �f�X�g���N�^
	~Stage() { Delete(); }

	// �t�@�C���̓ǂݍ���
	void Load();

	// �쐬
	bool Create(const float interval);

	// �`��
	void Draw(const DirectX::CommonStates& state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj);

	// �j��
	void Delete();

	// 
	std::vector<std::shared_ptr<LandShape>>	GetLandshape() { return m_pLandShapeArray; }

	//// �����̂����蔻��
	//Vector3* EvenCollision(Robot* robot);

	//// �����̂����蔻��
	//float VerticalCollision(Robot* robot);

private:
	// ���f���f�[�^�ǂݍ���
	void LoadModel(std::wifstream* file);

	// �}�b�v�f�[�^�ǂݍ���
	void LoadMap(std::wifstream* file);
};

